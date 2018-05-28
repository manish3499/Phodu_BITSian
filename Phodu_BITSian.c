/* This program can be used for two puposes
 * 1) To predict the end-sem marks of a student based on his mid-sem marks
 * 2) To analyse the performance of a student in his end-sem exam
 *
 * This program assumes that the performance of a student is a linear funtion of his mid-sem marks
 * 
 * We write this as :  
 *
 *      (marks secured by a student in end-sem) = a * (marks secured by him in mid-sem) + b 
 * 
 * for simplicity we denote end-sem marks of a student by "y" and the mid-sem marks by "x"
 *
 * now the equation takes the form :
 *
 *      y = a * x + b
 * where the values a and b are calculated by performing linear regression on the training examplesl */

#include <stdio.h>
#include <stdlib.h>


/* Define parameters that will be used to decide the performance of a student in his end-sem exam
 * VERY_GOOD_BASELINE when muliplied by the predictd end-sem marks gives a value which is used 
 * to determine if a student has performed vey well.
 * In a similar fashion other  constants are also used*/
 
#define VERY_GOOD_BASELINE 1.5
#define GOOD_BASELINE 1.1
#define BAD_BASELINE 0.8
#define VERY_BAD_BASELINE 0.5

// Struct used to store the mid-sem and end-sem marks of the training examples
typedef struct student{
	int midsem;
	int endsem;
	} STUD;

STUD *marks;

double a, b;
int N;

//performs linear regression on the values stored in the array of STUD datatype (containing the marks of the test cases)
void regression(); 


// predicts the end-sem marks of a student after linear regression has been performed on the training examples (prompts the user to provide his mid-sem marks)
void predict();

// Analyses the end-sem performance of a student (prompts the user to provide his mid-sem and end-sem marks)
void analyse();

int main()
{
	
	//The number of training examples
	printf("Enter the number of students (excluding you)\n"); 
	scanf("%d", &N);			 
	

	//creates an array of datatype STUD for all the training examples
	marks = malloc(sizeof(STUD) * N );


	//Prompts the user to provide the data about the training examples
	for ( int i = 0 ; i < N; i++)
	{	
		printf("Enter the mid-sem marks of the %dth student\t",i+1);
		scanf("%d",&marks[i].midsem);


		printf("Enter the compre marks of the %dth studnt\t",i+1);
		scanf("%d", &marks[i].endsem);
	}

	regression();

	char input;
	getchar();

	inp:
	printf("Do you want to predict or analyse your endsem marks? (enter a/p) \n");
	scanf("%c",&input);

	if ( input == 'a' || input == 'A' ) analyse();
	else if ( input == 'p' || input == 'P' ) predict();
	else 
	{
		printf( "INVALID INPUT\n");
		goto	inp;
	}	

}	

/* This function performs linear regression on the trainig examples.
 * the notation "sig_#" is used ot indicate that the variable is the sum of all (sigma) # values
 * for example "sig_x" is the variable used to store the sum of all (sigma) x values 
 * further, "sig_#n" represents the sum of all (sigma) # raised to the power n*/
void regression()
{
	double sig_y = 0, sig_y2 = 0, sig_x = 0, sig_x2 = 0, sig_xy = 0;
	

	// Calculates sigma x, sigma x^2, sigma y, sigma y^2 and sigma xy 
	for ( int i = 0; i < N; i++)
	{
		sig_x += marks[i].midsem;
		sig_x2 += marks[i].midsem * marks[i].midsem;
		sig_y += marks[i].endsem;
		sig_y2 += marks[i].endsem * marks[i].endsem;
		sig_xy += marks[i].midsem * marks[i].endsem;
	
	}



	// Calculates the parameter 'a' and 'b' in the equation y = a * x + b
	b = ( ( sig_y * sig_x2 ) - (sig_x * sig_xy) ) / ((N * sig_x2) - (sig_x * sig_x));
	a = ( ( N * sig_xy) - ( sig_x * sig_y) ) / ((N * sig_x2) - (sig_x * sig_x)) ;

	//Displays a and b on the screen
	printf("%lf\n",a);
	printf("%lf\n",b);
}

/* Used to predict the end-sem marks given the mid-sem marks of the student.
 * (The user is prompted to provide his mid-sem marks in this function)*/
void predict()
{
	int midsem;
	printf("Enter your mid-sem marks\t");
	scanf("%d",&midsem);
	
	//Predicts and displays the end-sem marks
	int predicted_endsem = a * midsem + b ;
	printf("Your predicted end-sem marks is: %d\n", predicted_endsem);
}

/* Used to predict the end-sem performance of a student in 
 * in comparison to his mid-sem performance */
void analyse()
{
 	int midsem, endsem;
	printf("Enter your mid-sem marks\t");
	scanf("%d",&midsem);
	printf("Enter your compre marks\t");
	scanf("%d",&endsem);


	//Generates predicted end-sem marks of the student
	int predicted_endsem = a * midsem + b;
	
	//Compares actual end-sem marks to predicted end-sem marks
	if ( endsem >= VERY_GOOD_BASELINE * predicted_endsem ) printf("Andha Phoda!!!!");
	else if ( endsem >= GOOD_BASELINE * predicted_endsem ) printf("Phoda!");
	else if ( endsem == predicted_endsem ) printf("Tum nahi badloge");
	else if ( endsem <= VERY_BAD_BASELINE * predicted_endsem) printf("Andha Haga. Padhlo abb bhi mauka hai"); 
	else if ( endsem <= BAD_BASELINE * predicted_endsem) printf("Haga :( ");


	printf("\n");
}
