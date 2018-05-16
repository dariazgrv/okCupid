#include <iostream>//library for inputs and outputs
#include <math.h>//library for math functions like sqrt
#include <fstream>//provides file stream classes
#define MAX_DIM 10 //defining a maximum number of users so it can be easly adjusted in the code if needed

using namespace std;

typedef struct { /*using a struct to store the user's id , question's id, answer given by the user,
				 answer preferred by the user and the importance of the answer*/

	int id, questionID, answer, acceptableAnswer, importance;


} User;

int Array1[MAX_DIM], Array2[MAX_DIM], aux2, aux3; //Array1 and Array2 will be used to store each id of the users when sorting in rank order


void quickSort(int ArrayOfPercentages[], int left, int right) { // using quicksort to sort the percentages

	int i = left, j = right;

	int aux;

	int pivot = ArrayOfPercentages[(left + right) / 2];



	/* partition part */

	while (i <= j) {

		while (ArrayOfPercentages[i] < pivot)

			i++;

		while (ArrayOfPercentages[j] > pivot)

			j--;

		if (i <= j) {
			//swapping the percentages
			aux = ArrayOfPercentages[i];

			ArrayOfPercentages[i] = ArrayOfPercentages[j];

			ArrayOfPercentages[j] = aux;

			//swapping the users at the same time we swap the percentages

			aux2 = Array1[i];
			Array1[i] = Array1[j];
			Array1[j] = aux2;

			aux3 = Array2[i];
			Array2[i] = Array2[j];
			Array2[j] = aux3;


			i++;

			j--;

		}

	};



	/* recursion part */

	if (left < j)

		quickSort(ArrayOfPercentages, left, j);

	if (i < right)

		quickSort(ArrayOfPercentages, i, right);



}

int main()
{

	int i, //index for traversing the array
		j, //another index
		score1 = 0, score2 = 0, // variables to store the score for each points
		totalUser1 = 0, totalUser2 = 0,// variables to score the total points of the importance of each question
		match,
		k = 0;//an index to increase the size of ArrayofPercentages

	int* ArrayOfPercentages;// an array to store the percentages
	ArrayOfPercentages = new int; // Request memory for the variable using new operator

	float percentUser1, percentUser2;

	ofstream f("output.txt");//Output file stream

	//using an array of struct to store each field of the User
	User user[MAX_DIM] = {
		{ 1,10,2,2,250 },
		{ 2,10,0,1,50 },
		{ 1,11,0,0,50 },
		{ 2,11,0,0,10 },
		{ 1,88,0,0,10 },
		{ 2,88,0,0,10 },
		{ 1,10,2,2,1 },
		{ 1,55,0,1,10 },
		{ 2,55,2,1,250 },
		{ 5,55,2,0,250 },

	};


	for (i = 0; i < MAX_DIM; i++)
	{


		for (j = i + 1; j < MAX_DIM - 1; j++)



			if (user[i].questionID == user[j].questionID)//checking if both answered the same question
			{


				if (user[i].acceptableAnswer == user[j].answer)
					/* if the second user gave the answer preferred by the first user ,
					we add the level of importance for that question of the first user*/

					score1 = score1 + user[i].importance;


				if (user[j].acceptableAnswer == user[i].answer)
					/* if the first user gave the answer preferred by the second user,
					we add the level of importance for that question of the second user*/

					score2 = score2 + user[j].importance;
			}

		totalUser1 = totalUser1 + user[i].importance;// we calculate the total number of points of the first user
		totalUser2 = totalUser2 + user[j].importance;// we calculate the total number of points of the second user

		percentUser1 = score2 / totalUser1;

		percentUser2 = score1 / totalUser2;

		match = sqrt(percentUser1 * percentUser2);

		ArrayOfPercentages[++k] = match;//stores each match into the array

		Array1[++k] = i;
		Array2[++k] = j;

	}



	quickSort(ArrayOfPercentages, 0, k);//calling the sorting function for printing the results of percentages in descending order

	f << "The top 10 matches are: ";

	for (i = k; i > k - 10; i--) // displaying only the first 10 matches in descending order
	{
		f << "User with the id " << Array1[i] << " has a " << ArrayOfPercentages[i] << " match with" << " user with the id " << Array2[i];
		f << endl;
	}


	// freed the allocated memory
	delete ArrayOfPercentages;

	return 0;

}


