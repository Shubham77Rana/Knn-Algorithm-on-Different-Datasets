#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <climits>
#include <cmath>

#define  DATA 1353
#define  ATTRIBUTES 10
#define  TRAINING_DATA 1053
#define  TESTING_DATA  300
#define  CLASSES 3
#define  START_KNN 1
#define  END_KNN 911

using namespace std;

struct class_distance
{
	float distance;
	float classes;
};

float actual_data[DATA][ATTRIBUTES];
float train_data[TRAINING_DATA][ATTRIBUTES];
float test_data[TESTING_DATA][ATTRIBUTES];
class_distance distance_array[TRAINING_DATA];

void randomize ( int arr[], int n )
{
    srand ( time(NULL) );
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swap(arr[i], arr[j]);
    }
}

void intialize_random_array(int random_array[])
{
        for(int i=0;i<DATA;i++)
                random_array[i] = i;
        randomize(random_array, DATA);
}

float distance(int index)
{
	for(int i=0;i<TRAINING_DATA;i++)
	{
		float d = 0;
		for(int j=0;j<ATTRIBUTES-1;j++)
		{
			d += pow(train_data[i][j] - test_data[index][j], 2);
		}
		distance_array[i].classes = train_data[i][ATTRIBUTES-1];
		distance_array[i].distance = sqrt(d);
	}
}

bool compare(class_distance a, class_distance b)
{
	return a.distance < b.distance;
}

int best_knn_evaluator(int KNN, int random_array[])
{
    float accuracy = 0;
    for(int i=0;i<TESTING_DATA;i++)
    {
	distance(i);
	int count[CLASSES] = {0};
	sort(distance_array, distance_array+TRAINING_DATA, compare);
	for(int j=0;j<KNN;j++)
	{
		for(int x=0;x<CLASSES;x++)
		{
			if(distance_array[j].classes == x)
			{
				count[x]++;
				break;
			}
		}
	}

	int max = INT_MIN, max_index;
	for(int x = 0;x<CLASSES;x++)
	{
		if(max < count[x])
		{
			max = count[x];
			max_index = x;
		}
	}

	if(max_index == test_data[i][ATTRIBUTES-1])
		accuracy ++;
     }

     return accuracy;
}

int main()
{
    int random_array[DATA];
    intialize_random_array(random_array);

    FILE *data = fopen("phishing.txt","r");
    int index = 0;
    float feature[ATTRIBUTES];

    while(fscanf(data, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &feature[0],
    &feature[1], &feature[2], &feature[3], &feature[4], &feature[5],
    &feature[6], &feature[7], &feature[8], &feature[9]) != EOF && index < DATA)
    {
	actual_data[index][0] = feature[0];
	actual_data[index][1] = feature[1];
	actual_data[index][2] = feature[2];
	actual_data[index][3] = feature[3];
	actual_data[index][4] = feature[4];
	actual_data[index][5] = feature[5];
	actual_data[index][6] = feature[6];
	actual_data[index][7] = feature[7];
	actual_data[index][8] = feature[8];
	actual_data[index][9] = feature[9]+1;

	index++;
    }

    index = 0;
    while(index < TRAINING_DATA)
    {
	train_data[index][0] = actual_data[random_array[index]][0];
	train_data[index][1] = actual_data[random_array[index]][1];
	train_data[index][2] = actual_data[random_array[index]][2];
	train_data[index][3] = actual_data[random_array[index]][3];
	train_data[index][4] = actual_data[random_array[index]][4];
	train_data[index][5] = actual_data[random_array[index]][5];
	train_data[index][6] = actual_data[random_array[index]][6];
	train_data[index][7] = actual_data[random_array[index]][7];
	train_data[index][8] = actual_data[random_array[index]][8];
	train_data[index][9] = actual_data[random_array[index]][9];

	index++;
    }

    int test_index = 0;
    while(index < DATA)
    {
	test_data[test_index][0] = actual_data[random_array[index]][0];
	test_data[test_index][1] = actual_data[random_array[index]][1];
	test_data[test_index][2] = actual_data[random_array[index]][2];
	test_data[test_index][3] = actual_data[random_array[index]][3];
	test_data[test_index][4] = actual_data[random_array[index]][4];
	test_data[test_index][5] = actual_data[random_array[index]][5];
	test_data[test_index][6] = actual_data[random_array[index]][6];
	test_data[test_index][7] = actual_data[random_array[index]][7];
	test_data[test_index][8] = actual_data[random_array[index]][8];
	test_data[test_index][9] = actual_data[random_array[index]][9];

	test_index++;
	index++;
    }

    float max_knn, max_accuracy;
    for(int i=START_KNN;i<=END_KNN;i++)
    {
        float temp_accuracy = best_knn_evaluator(i, random_array); 
	if(max_accuracy < temp_accuracy)
	{
		max_accuracy = temp_accuracy;
                max_knn = i; 
                cout << "New KNN found at accuracy " << (max_accuracy/TESTING_DATA)*100 << endl;
	}
    }

    cout << "Maximum Accuracy is " << (max_accuracy/TESTING_DATA)*100 << endl;
    cout << "Value of Optimum KNN is "<< max_knn << endl;

    return 0;
}
