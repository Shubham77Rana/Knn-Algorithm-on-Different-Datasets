#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <climits>
#include <cmath>

#define  DATA 2000
#define  ATTRIBUTES 16
#define  TRAINING_DATA 1500
#define  TESTING_DATA  500
#define  CLASSES 26
#define  START_KNN 501
#define  END_KNN 801

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
        //randomize(random_array, DATA);
}

float distance(int index)
{
	for(int i=0;i<TRAINING_DATA;i++)
	{
		float d = 0;
		for(int j=1;j<ATTRIBUTES;j++)
		{
			d += pow(train_data[i][j] - test_data[index][j], 2);
		}
		distance_array[i].classes = train_data[i][0];
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

	if(max_index == test_data[i][0])
		accuracy ++;
     }

     return accuracy;
}

int main()
{
    int random_array[DATA];
    intialize_random_array(random_array);

    FILE *data = fopen("letter-recognition.txt","r");
    int index = 0;
    float feature[ATTRIBUTES];
    float features;
    char str[10];

    while(index < DATA)
    {
	for(int i=0;i<ATTRIBUTES;i++)
	{
		if(i == 0)
		{
			fscanf(data, "%s,", str);
		}

		if(i != ATTRIBUTES-1)
			fscanf(data, "%f,", &features);
		else
			fscanf(data, "%f", &features);
		if(i != 0)
			actual_data[index][i] = features;
		else
		{
			switch(str[0])
			{
				case 'A': actual_data[index][i] = 0;
					  break;
				case 'B': actual_data[index][i] = 1;
					  break;
				case 'C': actual_data[index][i] = 2;
					  break;
				case 'D': actual_data[index][i] = 3;
					  break;
				case 'E': actual_data[index][i] = 4;
					  break;
				case 'F': actual_data[index][i] = 5;
					  break;
				case 'G': actual_data[index][i] = 6;
					  break;
				case 'H': actual_data[index][i] = 7;
					  break;
				case 'I': actual_data[index][i] = 8;
					  break;
				case 'J': actual_data[index][i] = 9;
					  break;
				case 'K': actual_data[index][i] = 10;
					  break;
				case 'L': actual_data[index][i] = 11;
					  break;
				case 'M': actual_data[index][i] = 12;
					  break;
				case 'N': actual_data[index][i] = 13;
					  break;
				case 'O': actual_data[index][i] = 14;
					  break;
				case 'P': actual_data[index][i] = 15;
					  break;
				case 'Q': actual_data[index][i] = 16;
					  break;
				case 'R': actual_data[index][i] = 17;
					  break;
				case 'S': actual_data[index][i] = 18;
					  break;
				case 'T': actual_data[index][i] = 19;
					  break;
				case 'U': actual_data[index][i] = 20;
					  break;
				case 'V': actual_data[index][i] = 21;
					  break;
				case 'W': actual_data[index][i] = 22;
					  break;
				case 'X': actual_data[index][i] = 23;
					  break;
				case 'Y': actual_data[index][i] = 24;
					  break;
				case 'Z': actual_data[index][i] = 25;
					  break;
			}	
		}
	}

	index++;
    }

    index = 0;
    while(index < TRAINING_DATA)
    {
	for(int i=0;i<ATTRIBUTES;i++)
	{
		train_data[index][i] = 	actual_data[random_array[index]][i];
	}

	index++;
    }

    int test_index = 0;
    while(index < DATA)
    {
	for(int i=0;i<ATTRIBUTES;i++)
	{
		test_data[test_index][i] = actual_data[random_array[index]][i];
	}

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
