#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

double leave_one_out_cross_validation(vector<vector<double>>& data, vector<int>& current_set, int feature_to_add);
void feature_search(vector<vector<double>>& data, vector<int>& current_set_of_features);
bool isempty(vector<int>& current_set_of_features, int j);

int main() {
    ifstream inFS, inFS_Column_Size; // Used to get the data in the given data files
    vector<vector<double>> data; // Used to hold the values in the data files
    vector<double> values;
    vector<int> current_set;

    int choice, column_size;
    double value;
    string data_option;

    cout << "Choose one of the following options: " << endl;
    cout << "1: If you want the Small DataSet." << endl;
    cout << "2: If you want the Large DataSet." << endl;
    cout << "3: If you want to insert another text-file." << endl;

    cin >> choice;

    while(choice != 1 && choice != 2 && choice != 3) {
        cin.ignore();
        cout << "Not a valid input, try again." << endl;
        cin >> choice;
    }

    // Unlike Matlab, we cannot determine the end of a row easily, so we initiate the columns to include class type and features from the start
    // Also here, given we have two specific dataset, we just hardcode both file names

    if(choice == 1) { 
        data_option = "CS170_Small_DataSet__51.txt";
    } else if (choice == 2) {
        data_option = "CS170_Large_DataSet__27.txt";
    } else {
        cout << "Type the file name below:" << endl;
        cin >> data_option;
    }

    inFS.open(data_option);
    inFS_Column_Size.open(data_option);

    if(!inFS.is_open()) {
        cout << data_option << " could not be opened." << endl;
        return 0;
    }

    // This is used to determine how many columns there are to separate the instances per row

    string line;
    int count = 0;

    getline(inFS_Column_Size, line);

    for(int i = 0; i < line.length(); ++i) { 
        if(line.at(i) == 'e') { // we can use e here since each IEEE contains an e per column
            ++count;
        }
    }

    column_size = count;
    
    cout << "Choose one of the following options: " << endl;
    cout << "1: If you want Forward Selection." << endl;
    cout << "2: If you want Backward Elimination." << endl;
    
    cin.ignore();
    cin >> choice;

    while(choice != 1 && choice != 2) {
        cin.ignore();
        cout << "Not a valid input, try again." << endl;
        cin >> choice;
    }
    
    // This is used for Backward Elimiantion where we begin with all features, Small Data is 16 features and Large Data is 64
    if(choice == 2) {
        for(int i = 1; i < column_size; ++i) {  
            current_set.push_back(i);
        }
    }

    while(inFS >> value) {
        if(values.size() == column_size) { // this is to separate the rows of data, where each row represents an instance with differing feature data
            data.push_back(values);
            values.clear();
        }
        values.push_back(value);
    }

    data.push_back(values);

    feature_search(data, current_set);

    return 0;
}

// The majority of the functions below are the ones provided in the Program 2 Cheat Sheet

void feature_search(vector<vector<double>>& data, vector<int>& current_set_of_features) {
    double default_rate, class_1_type, class_2_type; // This is the deafult rate for no features, but will not be used when finding best features (as there would be none)
    vector<int> best_current_set, copy_set;
    int feature_to_add, feature_to_remove;
    double max_best_accuracy, best_so_far_accuracy, accuracy;
    int initial_value_size = current_set_of_features.size(); // Used to determine whether to do forward selection or backward elimination

    for(int i = 0; i < data.size(); ++i) {
        if(data[i][0] == 1) {
            ++class_1_type;
        } else {
            ++class_2_type;
        }
    }

    if(class_1_type > class_2_type) {
        default_rate = class_1_type * 1.0 / (class_1_type + class_2_type);
    } else {
        default_rate = class_2_type * 1.0 / (class_1_type + class_2_type);
    }

    if(initial_value_size == 0) {
        cout << "Feature set {} was best, accuracy was " << default_rate * 100 << "%, but will not be included as a possible subset." << endl;
    } else {
        max_best_accuracy = leave_one_out_cross_validation(data, current_set_of_features, 0);
        
        cout << "Feature set {";

        for(int i = 0; i < current_set_of_features.size(); ++i) {
            cout << current_set_of_features[i];
            
            if(i != current_set_of_features.size()-1) {
                cout << ",";
            }
        }

        cout << "} was best, accuracy was " << max_best_accuracy << endl;
    }

    for(int i = 1; i < data[0].size(); ++i) { // this just runs all the features excluding class type, hence i = 1 and data[0].size() is just the row size (1-17 and 1-65)
        best_so_far_accuracy = 0;
    
        if(initial_value_size == 0) { // If the feature size was initially zero, then we must be running forward selection
            for(int j = 1; j < data[0].size(); ++j) { // This runs until we find the feature with the best accuracy (adds one by one) 
                if(isempty(current_set_of_features, j) == true) { // Make sure the feature is not already in our set
                    accuracy = leave_one_out_cross_validation(data, current_set_of_features, j);
                    
                    cout << "Using feature(s) {";

                    for(int k = 0; k < current_set_of_features.size(); ++k) {
                        cout << current_set_of_features[k] << ",";
                    }

                    cout << j << "}" << " accuracy is " << accuracy << "%" << endl;
                    if(accuracy > best_so_far_accuracy) {
                        best_so_far_accuracy = accuracy;
                        feature_to_add = j;
                    }
                }
            }
        } else { // If initial size was not zero, then we must be running backward elimination
            if(i == data[0].size() - 1) { // This is needed to not run the empty/no feature set, which we do at the end
                break;
            }

            for(int j = 1; j <= current_set_of_features.size(); ++j) {
                copy_set = current_set_of_features;
                copy_set.erase(copy_set.begin() + j - 1); // Removes the feature from the set, but we need to offset by 1 since vectors start at 0
                accuracy = leave_one_out_cross_validation(data, copy_set, 0); // Here since we do not add a feature, we hardcode feature to add to 0

                cout << "Using features(s) {";

                for(int k = 0; k < copy_set.size(); ++k) {
                    cout << copy_set[k];

                    if(k != copy_set.size()-1) {
                        cout << ",";
                    }
                }
                cout << "}" << " accuracy is " << accuracy << "%" << endl;
                
                if(accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_remove = j;
                }
            }
        }

        if(initial_value_size == 0) {
            current_set_of_features.push_back(feature_to_add); // This is where we add the feature into our set (again, one by one)
        } else {
            current_set_of_features.erase(current_set_of_features.begin() + feature_to_remove - 1); // Removes the feature that when removed, provided the best accuracy (offset by 1)
        }

        if(best_so_far_accuracy > max_best_accuracy) {
            max_best_accuracy = best_so_far_accuracy;
            best_current_set = current_set_of_features;
        }

        cout << "Feature set {";

        for(int j = 0; j < current_set_of_features.size(); ++j) {
            cout << current_set_of_features[j];

            if(j == current_set_of_features.size()-1) {
                cout << "}";
            } else {
                cout << ",";
            }
        }

        cout << " was best, accuracy was " << best_so_far_accuracy << "%" << endl;
    }
    cout << "Feature set {} was best, accuracy was " << default_rate * 100 << "%, but will not be included as a possible subset." << endl;

    cout << "The best feature subset is {";

    for(int i = 0; i < best_current_set.size(); ++i) {
        cout << best_current_set[i];

        if(i == best_current_set.size()-1) {
            cout << "}";
        } else {
            cout << ",";
        }
    }

    cout << " which has an accuracy of " << max_best_accuracy << "%" << endl;

    cout << "Time took is: " << clock()/(1.0 * CLOCKS_PER_SEC) << endl; // This is the time and clock function that I learned in Project 1
}

bool isempty(vector<int>& current_set_of_features, int j) { // This function main purpose is for Forward Selection to not repeat features already in our set
    for(int i = 0; i < current_set_of_features.size(); ++i) {
        if(current_set_of_features[i] == j) {
            return false;
        }
    }
    return true;
}

double leave_one_out_cross_validation(vector<vector<double>>& data, vector<int>& current_set, int feature_to_add) { // This function is where we determine the accuracy given the feature set
    double nearest_neighbor_distance, nearest_neighbor_location, nearest_neighbor_label;
    double distance, total_sum, sum, accuracy, label_object_to_classify, number_correctly_classified = 0;
    
    for(int i = 1; i <= data.size(); ++i) { // This is to get all possible instances, i.e the data size

        label_object_to_classify = data[i-1][0]; // Class type again is always at the front, i.e. position 0

        nearest_neighbor_distance = 1000000; // Instead of inf like in the cheat sheet, 1000000 should be big enough
        nearest_neighbor_location = 1000000;

        for(int j = 1; j <= data.size(); ++j) { // This is to get all possible instances, i.e the data size

            if(j != i) { // This is to make sure we don't compare ourselves
                total_sum = sum = distance = 0;

                // D(Q,C) = sqrt(sum from i=1 to n (qi - ci)^2)
                for(int k = 0; k < current_set.size(); ++k) { // this is the Euclidean Distance equation
                    int l = current_set[k]; // This is to get the value of the features in the current set

                    sum = data[i-1][l] - data[j-1][l]; // This compares all available features, given by l, from all instances in the dataset
                    total_sum += sum * sum; // Then we square the equals and keep track of the total sum
                }
 
                if(feature_to_add != 0) { // This is only needed for Forward Selection (i.e. when feature to add is not 0)
                    sum = data[i-1][feature_to_add] - data[j-1][feature_to_add];
                    total_sum += sum * sum;
                }

                distance = sqrt(total_sum); 

                if(distance < nearest_neighbor_distance) { // This becomes the best/nearest neighbor if true
                    nearest_neighbor_distance = distance;
                    nearest_neighbor_location = j; // j is offset by 1 in a vector, so that is fixed in the label
                    nearest_neighbor_label = data[nearest_neighbor_location-1][0]; // the class type is always at the top remember i.e. 0
                }
            }
        }

        if(label_object_to_classify == nearest_neighbor_label) { // Used to determine whether or not our classification was correct
            number_correctly_classified += 1;
        }
    }
    
    accuracy = number_correctly_classified * 1.0 / (data.size()) * 100; // This is used for the accuracy which is turned into a percentage

    return accuracy;
}