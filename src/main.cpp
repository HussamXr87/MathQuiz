#include <iostream>
#include <cstdlib>
#include <string>

enum enQuestionLevel {EASY = 1, MEDIUM = 2, HARD = 3, MIX = 4};
enum enQuestionOP {ADD = 1, SUB = 2, MULT = 3, DIV = 4, MIX_OP = 5};


struct stQuestion {
    int FirstNumber = 0;
    int SecondNumber = 0;
    int UserAnswer = 0;
    int CorrectAnswer = 0;
    bool QuestionResult;
};

struct stQuiz {
    stQuestion Question[100];
    enQuestionLevel QuestionLevel;
    enQuestionOP QuestionOp;
    int QuestionsNumber = 0;
    int WrongAnswer = 0;
    int RightAnswer = 0;
    bool QuizResult;

};

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

int ReadPositiveNumber(std::string Message) {

    int Number = 0;
    do {
        std::cout << Message;
        std::cin >> Number;
    }while(Number <= 0);
    return Number;

}

enQuestionOP ReadQuestionOP(std::string Message) {
    short Number = 0;
    do {
        std::cout << Message;
        std::cin >> Number;
    }while(Number > 5 || Number < 1);

    if(Number == 5)
        return (enQuestionOP)RandomNumber(1,3);

    else 
        return (enQuestionOP)Number;
}

enQuestionLevel ReadQuestionLevel(std::string Message) {
    short Number = 0;
    do {
        std::cout << Message;
        std::cin >> Number;

    } while(Number > 4 || Number < 1);

    if(Number == 4)
        return (enQuestionLevel)RandomNumber(1,3);

    else 
        return (enQuestionLevel)Number;
}

std::string GetOpName(enQuestionOP QuestionOP) {
    std::string Names[4] = {"+", "-", "*", "/"};
    return Names[QuestionOP - 1];
}

int ReadUserAnswer(stQuestion Question, enQuestionOP QuestionOP) {
    int Number;
    std::cout << Question.FirstNumber << " " << GetOpName(QuestionOP) << std::endl;
    std::cout << Question.SecondNumber << "\n_________________\n";
    std::cin >> Number;
    std::cout << std::endl;
    return Number;
    
}

int SimpleCalculater(int FirstNumber, int SecondNumber, enQuestionOP QuestionOP) {
    
    switch (QuestionOP) {
        case enQuestionOP::ADD:
            return FirstNumber + SecondNumber;

        case enQuestionOP::SUB:
            return FirstNumber - SecondNumber;

        case enQuestionOP::MULT:
            return FirstNumber * SecondNumber;

        case enQuestionOP::DIV:
            return FirstNumber / SecondNumber;

    };
}

int GenrateNumberByLevel(enQuestionLevel QuestionLevel) {

    switch (QuestionLevel)
    {
        case enQuestionLevel::EASY: 
            return RandomNumber(1,10);

        case enQuestionLevel::MEDIUM:
            return RandomNumber(1,50);
        
        case enQuestionLevel::HARD:
            return RandomNumber(1,100);
    };
}

stQuestion GenrateQuestion(enQuestionLevel QuestionLevel, enQuestionOP QuestionOP) {
    
    stQuestion Question;

    Question.FirstNumber = GenrateNumberByLevel(QuestionLevel);
    Question.SecondNumber = GenrateNumberByLevel(QuestionLevel);

    Question.CorrectAnswer = SimpleCalculater(Question.FirstNumber, Question.SecondNumber, QuestionOP);
    Question.UserAnswer = ReadUserAnswer(Question, QuestionOP);

    Question.QuestionResult = Question.CorrectAnswer == Question.UserAnswer;

    return Question;
    
    
}

void ShowQuestionResult(stQuestion Question) {
    if(Question.QuestionResult) {
        std::cout << "\nYou Answer this question right ^_^\n";
    }
    else {
        std::cout << "\nYou Answer this question wrong :-( \n";
    }
}

stQuiz PlayGame() {

    stQuiz Quiz;
    Quiz.QuestionsNumber = ReadPositiveNumber("\nHow many questions do you want to solve (please type a positive number): ");
    Quiz.QuestionLevel = ReadQuestionLevel("\nWhat Questions Level do you want (1 => EASY, 2 => MEDIUM, 3 => HARD, 4 => MIX): ");
    Quiz.QuestionOp = ReadQuestionOP("\nWhat Operations type do you want to solve (ADD => 1, SUB => 2, MULT => 3, DIV => 4, MIX => 5 ): ");
    
    for(int i = 0; i < Quiz.QuestionsNumber; i++) {

        std::cout << "\nQuestion Number: " << i + 1 << std::endl;

        Quiz.Question[i] = GenrateQuestion(Quiz.QuestionLevel, Quiz.QuestionOp);

        ShowQuestionResult(Quiz.Question[i]);

        if(Quiz.Question[i].QuestionResult == true) {
            Quiz.RightAnswer++;
        }
        else {
            Quiz.WrongAnswer++;
        }
    }
    Quiz.QuizResult = (Quiz.RightAnswer >= Quiz.WrongAnswer);
    return Quiz;
    
}
void ShowGameResult(stQuiz Quiz) {
    std::cout << "\n\n_______________________________\n";
    std::cout << "You Answer " << Quiz.RightAnswer << " Question Right" << std::endl;
    std::cout << "You Answer " << Quiz.WrongAnswer << " Question Wrong" << std::endl;
    if(Quiz.QuizResult)
        std::cout << "You Passed The Quiz ^_^\n";
    else 
        std::cout << "You Didnt Pass The Quiz : - ( \n";

}
void StartGame() {

    char PlayAgain = 'Y';

    do {
        system("clear");
        stQuiz Quiz = PlayGame();
        ShowGameResult(Quiz);
        std::cout << "\nDo you want to play Again: ";
        std::cin >> PlayAgain;
    }while(PlayAgain == 'Y' || PlayAgain == 'y');

}
int main() {
    srand(unsigned(time(NULL)));
    StartGame();
    return 0;
}