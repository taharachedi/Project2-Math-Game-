#include <iostream>
#include <cstdlib>

using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };


struct stQuestion {
	short Number1 = 0;
	short Number2 = 0;
	enQuestionsLevel QuestionLevel;  
	enOperationType OperationType;
	short CorrectAnswer = 0;
	short PlayerAnswer = 0;
	bool AnswerResult = false;
};


struct stQuizz {
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel Qst_Level;
	enOperationType Op_Type;  
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = false;
};


short Read_HowManyQuestions() {
	short Q = 0;

	do
	{
		cout << "How Many Questions : (1 => 10) ";
		cin >> Q;

	} while (Q < 1 || Q > 10);

	return Q;
}



enQuestionsLevel Read_QuestionsLevel() {    
	short Q = 0;

	do
	{
		cout << "Enter Questions Level :  [1]:Easy , [2]:Med , [3]:Hard , [4]:Mix  ? ";
		cin >> Q;

	} while (Q < 1 || Q > 4);

	return (enQuestionsLevel)Q;
}


string Get_QuestionsLevel_Text(enQuestionsLevel Level) {
	string arrLevel[4] = { "Easy" , "Med" , "Hard" , "Mix" };

	return arrLevel[Level - 1];
}



enOperationType Read_OpType() {
	short Op = 0;

	do
	{
		cout << "Enter Operation Type :  [1]:Add , [2]:Sub , [3]:Mul , [4]:Div , [5]:Mix  ?";
		cin >> Op;

	} while (Op < 1 || Op > 5);

	return (enOperationType)Op;
}


string Get_OpType_Symbol(enOperationType Op) {

	switch (Op)
	{
	case enOperationType::Add:
		return "+";

	case enOperationType::Sub:
		return "-";

	case enOperationType::Mult:
		return "x";

	case enOperationType::Div:
		return "/";

	default:
		return "Mix";
	}
}

////////////////////////////////////////////////////////////////////////////////////////////


short Random_Number(short From, short To) {
	return rand() % (To - From + 1) + From;
}


enQuestionsLevel Get_Random_QuestionsLevel() {
	return (enQuestionsLevel)Random_Number(1, 3); 
}


enOperationType Get_Random_OpType() {
	return (enOperationType)Random_Number(1, 4);
}


////////////////////////////////////////////////////////////////////////////////////////////


short SimpleCalculator(short N1, short N2, enOperationType Op) {

	switch (Op)
	{
	case enOperationType::Add:
		return N1 + N2;

	case enOperationType::Sub:
		return N1 - N2;

	case enOperationType::Mult:
		return N1 * N2;

	case enOperationType::Div:
		return N1 / N2;

	}
}


stQuestion GenerateQuestion(enQuestionsLevel Q_Level, enOperationType OpType) {

	stQuestion Q;

	if (Q_Level == enQuestionsLevel::Mix)
		Q_Level = Get_Random_QuestionsLevel();

	if (OpType == enOperationType::MixOp)  
		OpType = Get_Random_OpType();

	Q.OperationType = OpType;

	switch (Q_Level)
	{
	case enQuestionsLevel::Easy:
		Q.Number1 = Random_Number(1, 10);
		Q.Number2 = Random_Number(1, 10);

		Q.CorrectAnswer = SimpleCalculator(Q.Number1, Q.Number2, Q.OperationType);
		Q.QuestionLevel = Q_Level; 
		
		return Q;



	case enQuestionsLevel::Med:
		Q.Number1 = Random_Number(10, 50);
		Q.Number2 = Random_Number(10, 50);

		Q.CorrectAnswer = SimpleCalculator(Q.Number1, Q.Number2, Q.OperationType); 
		Q.QuestionLevel = Q_Level; 

		return Q;


	case enQuestionsLevel::Hard:
		Q.Number1 = Random_Number(50, 100);
		Q.Number2 = Random_Number(50, 100);

		Q.CorrectAnswer = SimpleCalculator(Q.Number1, Q.Number2, Q.OperationType); 
		Q.QuestionLevel = Q_Level; 

		return Q;
	}
	return Q;
}




void GenerateQuizzQuestions(stQuizz &Quizz) {

	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.Qst_Level, Quizz.Op_Type);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////


void Print_TheQuestion(stQuizz& Quizz, short Q_Number) {

	cout << "\n";
	cout << "Question [" << Q_Number + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[Q_Number].Number1 << endl;
	cout << Quizz.QuestionList[Q_Number].Number2 << "  ";
	cout << Get_OpType_Symbol(Quizz.QuestionList[Q_Number].OperationType);
	cout << "\n_________________" << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void Set_ScreenColor(bool Right) {

	if (Right)
		system("color 2F"); //Green
	else
	{
		system("color 4F"); //Red
		cout << "\a";
	}
}


void Correct_TheQuestionAnswer(stQuizz& Quizz, short Q_Number) {

	if (Quizz.QuestionList[Q_Number].PlayerAnswer != Quizz.QuestionList[Q_Number].CorrectAnswer) {

		Quizz.QuestionList[Q_Number].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer  : -( \n";
		cout << "The Right Answer is : " << Quizz.QuestionList[Q_Number].CorrectAnswer << endl;
	}
	else {
		Quizz.QuestionList[Q_Number].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer : -) \n";
	}
	cout << endl;

	Set_ScreenColor(Quizz.QuestionList[Q_Number].AnswerResult);
}

////////////////////////////////////////////////////////////////////////////////:

short Read_PlayerAnswer() {
	short Answer = 0;

	cin >> Answer;
	return Answer;
}




void Ask_And_Correct_QuestionsListAnswers(stQuizz& Quizz) {

	for (short Question_Number = 0; Question_Number < Quizz.NumberOfQuestions; Question_Number++)
	{
		Print_TheQuestion(Quizz, Question_Number);
		Quizz.QuestionList[Question_Number].PlayerAnswer = Read_PlayerAnswer(); 
		Correct_TheQuestionAnswer(Quizz, Question_Number);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

//////////////////////////////////////////////////////////////

string Get_FinalResultText(bool Pass) {

	if (Pass)
		return "PASS : -) ";
	else
		return "FAIL : -( ";
}


void Print_QuizzResults(stQuizz Quizz) {

	cout << "\n";

	cout << "_____________________________________________________________\n\n";
	cout << "Final Results is : " << Get_FinalResultText(Quizz.isPass) << endl;
	cout << "_____________________________________________________________\n\n";

	cout << "Number Of Questions       : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level           : " << Get_QuestionsLevel_Text(Quizz.Qst_Level) << endl;
	cout << "Operation Type            : " << Get_OpType_Symbol(Quizz.Op_Type) << endl; 
	cout << "Number Of Right Questions : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Questions : " << Quizz.NumberOfWrongAnswers << endl;

	cout << "_____________________________________________________________\n\n";
}


void Play_MathGame() {

	stQuizz Quizz;

	Quizz.NumberOfQuestions = Read_HowManyQuestions();
	Quizz.Qst_Level = Read_QuestionsLevel(); 
	Quizz.Op_Type = Read_OpType();

	GenerateQuizzQuestions(Quizz);
	Ask_And_Correct_QuestionsListAnswers(Quizz);
	Print_QuizzResults(Quizz);
}


void ResetScreen() {
	system("cls");
	system("color 0F");
}


void StartGame() {

	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		Play_MathGame();

		cout << endl << "Do U want To Play Again (Y/N) ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}



int main()
{
	srand((unsigned)time(NULL));

	StartGame();


	system("pause>0");
    return 0;
}