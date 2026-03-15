# CS170 Project 2: Feature Selection with Nearest Neighbor

Erik Torres

SID# 862462457

Email: etorr153@ucr.edu

Date: March 16, 2026

# **In this assignment, I used:**

* Project 1 and 2 sample report for format/structure, examples, and outputs
* Google Sheets to make charts shown in this report (with respective data), also found here: https://docs.google.com/spreadsheets/d/1YEdcOs-JxFe-ItaBJqkOOkXMNOZZIXtvy9xaTBgTsBA/edit?usp=sharing

# **Parts of the code that are unoriginal/used for help are:**

* Leave one out cross validation and feature search functions that were in Project 2 Cheat Sheet slides and video for coding and explanations. 
* Slides: https://www.dropbox.com/scl/fo/blbkjaf1eyl94lij5wl2b/AAvNKn0YrnaX0oGPQn7ueFo?dl=0&e=2&preview=Project_2_Cheat_Sheet.pptx&rlkey=alq2gb2ftsw73hcar4lk897r0
* Video: https://www.dropbox.com/scl/fi/j7psoqfj89gmkbiv1ka5i/Project_2_Briefing_video.mp4?rlkey=btj2dii7on2efutxeps0dwnan&e=2&dl=0

# **Outline of this Report:**

* Cover Page: Page 1
* Report: Pages 2-6
* Small Data Forward Selection Problem Example: Page 7
* Small Data Backward Elimination Problem Example: Page 8 
* Code found on here

# **Introduction:**

Feature Selection with Nearest Neighbor Classification is a project where we classify data using Nearest Neighbor Selection, in our given datasets, which I have done in C++. Then, we use Forward Selection or Backward Elimination search to determine which provides the best time and accuracy. This project, although isolated to two datasets, can be applied generally in the industry to help save time, memory, and money. 

This project utilized one algorithm, Nearest Neighbor Classification and two different searches, Forward Selection, which adds one feature at a time and Backward Elimination, which removes one feature at a time, to help determine the best features that provide the highest accuracy. Some things to keep in mind are, “You will almost certainly find that forward and backward search give different answers” [1], as well as “Forward search tends to be better on almost all problems” [1].

[1] P2_hints (Eammon Keogh, 2026, UCR, Slides/Dropbox Pg. 1)

# **Nearest Neighbor Algorithm:**

For Nearest Neighbor Classification in a visual sense, the data is separated into regions so that no regions contain two different classes of data. Here, lines are more expressive and no longer need to be straight lines, as seen in Figure 1 [2]:

 ![alt text](https://github.com/eriktorres43/CS170-Project-2/blob/Pictures/Figure1.png?raw=true)
               
This algorithm typically uses Euclidean Distance on feature data to determine an unknown instance’s nearest neighbor and classifies the instance with the same class type as its nearest neighbor. Then, we compare the classified class type to the actual class and see how many classifications were correctly classified, and then we divide by the number of instances in our dataset (K-fold Cross Validation) to measure accuracy, where K is the number of rows in the dataset. But, we know that “The nearest neighbor algorithm is sensitive to irrelevant features…” [3], so we use the searches to find the features that maximize accuracy. 

[2] 6__MachineLearning001 (Eammon Keogh, 2026, UCR, Slides/Dropbox Pg.66)

[3] 6__MachineLearning001 (Eammon Keogh, 2026, UCR, Slides/Dropbox Pg. 74)

# **Small Dataset:**

In Figure 2, we see the results of running Forward Selection on CS170_Small_DataSet__51.txt, the dataset assigned to me:

 ![alt text](https://github.com/eriktorres43/CS170-Project-2/blob/Pictures/Figure2.png?raw=true)

Before beginning to search, we first start with no features, also denoted by {}, whose accuracy is calculated by using the default rate, “the size of the most common class, over the size of the full dataset” [4], which in this case, is 85.8%. Some conclusions that can be made from the graph are that adding {8} mostly maintained the accuracy with 85.4%, but when adding {13}, it caused the accuracy to increase to 95.8%. After this, the chart continues a gradual decline of accuracy, meaning no further features were useful, which ends with an accuracy of 77.2%. Hence, features {8} and {13} are the best. 

[4] 7__MachineLearning002 (Eammon Keogh, 2026, UCR, Slides/Dropbox Pg.4)


In Figure 3, we see the results of running Backward Elimination on CS170_Small_DataSet__51.txt, the dataset assigned to me:
 
 ![alt text](https://github.com/eriktorres43/CS170-Project-2/blob/Pictures/Figure3.png?raw=true)

Before beginning to search, we first start with all features, whose accuracy is the same as that of Forward Selection, 77.2%. As we begin removing features one by one, we can see that removing 3 features (4th bar) reaches the highest accuracy, ignoring no features ({}), but the increase isn’t significant and slowly decreases past this point. Since this increase wasn’t significant, this could indicate that none of these features are useful, which is explained by the highest accuracy being the default rate. However, if features are needed, which the code does, the best feature set is {1,2,3,4,5,6,7,9,11,12,13,14,15}. 

# **Small Dataset Conclusion:**

After looking at both Forward Selection and Backward Elimination, I believe that feature {13} was the best feature as it was contained in both searches for this specific dataset. The rest of the features that are included in the sets don’t show enough evidence of being useful. Therefore, implementing the set {8,13}, I believe the accuracy will be 95.8% if we see data similar to this dataset moving forward and using Forward Selection. 

# **Large Dataset:**

In Figure 4, we see the results of Forward Selection on CS170_Large_DataSet__27.txt, the dataset assigned to me: 

 ![alt text](https://github.com/eriktorres43/CS170-Project-2/blob/Pictures/Figure4.png?raw=true)

Similar to the small dataset, we begin with no features, denoted by {}, whose accuracy is still calculated using the default rate equation, which is 82%. Starting Forward Selection search, adding feature {42} helped increase the accuracy to 83.97% and adding feature {40} leads to an even bigger increase with an accuracy of 97.2%. However, past this point, we steadily decline in accuracy, ending with an accuracy of 67.1%, leading to no additional useful features. Therefore, the only useful features are {40} and {42}. 

In Figure 5, we see the results of Backward Elimination on CS170_Large_DataSet__27.txt, the dataset assigned to me: 

 ![alt text](https://github.com/eriktorres43/CS170-Project-2/blob/Pictures/Figure5.png?raw=true)

Similar to the small dataset, we begin with all features, whose accuracy starts at 67.1%, the same accuracy seen in Forward Selection. As we remove features one by one, we can see that accuracy slowly increases for the majority of features removed, typically implying non-important features. However, near the end, we can see that feature {42} showed the biggest increase in accuracy from 83.83% to 89.93% compared to the rest. At the end, with no features, we get an accuracy decrease to 82%, same as the one seen in Forward Selection, meaning that the best feature from this search is {42}.

# **Large Dataset Conclusion:**

After looking at both Forward Selection and Backward Elimination, I believe that feature {42} was the best feature as it was contained in both searches for this dataset. The rest of the features that are included in the sets don’t show enough evidence of being useful compared to {42}. Hence, implementing the set {40,42}, I believe the accuracy will be 97.2% if we see a dataset similar to this dataset moving forward using Forward Selection. 

# **Time Analysis:**

Of course, accuracy is the most important factor when choosing which algorithm to use, but runtime can also be a big factor, especially if you can get the same, if not better, accuracy in a shorter amount of time. Below in Table 1, we can see how runtime differs not only between the different searches but also between the datasets, with increasing instances and features.

 ![alt text](https://github.com/eriktorres43/CS170-Project-2/blob/Pictures/Table1.png?raw=true)

Based on this data, we can see that not surprisingly, the small dataset ran faster than the large dataset, given its smaller number of features (16 compared to 64) and instances (500 compared to 3000). Additionally, we can see that Forward Selection was not only better in terms of accuracy, but also in terms of runtime, doing roughly 1.62 and 1.86 times better than Backward Elimination. This could be caused by Forward Selection searching for all features with smaller feature subsets compared to Backward Elimination. 

# **Conclusion:**

After all the information for Forward Selection and Backward Elimination, we can conclude and verify the given facts to look out for at the beginning of the report. In the first case, the two searches did give different results (feature sets) for both datasets. In the second case, for both datasets as well, we can see that Forward Selection always gave a better accuracy than Backward Elimination. But of course, not only was accuracy measured, but also time, which Forward Selection also performed better in. 

Therefore, when attempting to solve this problem again, whether that be for this class or in the industry, I would recommend solving these problems using Forward Selection, as its accuracy and runtime performed better than Backward Elimination, given similar datasets to those provided in this project.

# **Examples:**

The next two pages contain examples of the output of running Small Dataset Forward Selection and Small Dataset Backward Elimination.

This is the example and output of Small Dataset Forward Selection:

 ![alt text](https://github.com/eriktorres43/CS170-Project-2/blob/Pictures/Example1.png?raw=true)

This is the example and output of Small Dataset Backward Elimination:

 ![alt text](https://github.com/eriktorres43/CS170-Project-2/blob/Pictures/Example2.png?raw=true)
