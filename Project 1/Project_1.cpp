#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;



struct stGamePlayerData
{
  short PlayerInput = 0, ComputerInput = 0;
  short PlayerPoints = 0, ComputerPoints = 0, DrawTimes = 0;
};
enum enWinnerIs
{
  NoWinner = 0,
  Player = 1,
  Computer = 2
};
enum enChoice
{
  Paper = 1,
  Stone = 2,
  Scissors = 3
};

int ReadNumberInRange(string Message, int From, int To)
{
  int Number = 0;
  do
  {
    cout << Message;
    cin >> Number;
  } while (Number < From || Number > To);
  return Number;
}
char AskAboutAgainGame()
{
  char DoYouWantToPlayAgain;
  do
  {
    cout << "Do You Want to Play Again? Y/N?";
    cin >> DoYouWantToPlayAgain;
    cout << endl;
  
  } while (DoYouWantToPlayAgain != 'Y' && DoYouWantToPlayAgain != 'y' && DoYouWantToPlayAgain != 'N' && DoYouWantToPlayAgain != 'n');

return DoYouWantToPlayAgain;

}
short AskAboutRounds()
{
  short Rounds = ReadNumberInRange("How Many Rounds 1 to 10?\n", 1, 10);
  return Rounds;
}

int RandomNumber(int From, int To)
{
  int randNum = rand() % (To - From + 1) + From;
  return randNum;
}

stGamePlayerData ReadPlayersChoices()
{
  stGamePlayerData GamePlayersData;

  // Computer Player:

  GamePlayersData.PlayerInput = ReadNumberInRange(
      "Your Choice: [1]:Paper, [2]:Stone, [3]:Scissors ? ", 1, 3);

  // Computer Choice:

  GamePlayersData.ComputerInput = RandomNumber(1, 3);

  return GamePlayersData;
}


short HowIsWinner(stGamePlayerData GamePlayersData)
{

  short PlayerChoice = GamePlayersData.PlayerInput;
  short ComputerChoice = GamePlayersData.ComputerInput;
  if (PlayerChoice == ComputerChoice)
  {
    return enWinnerIs::NoWinner;
  }
  else if ((PlayerChoice == enChoice::Stone &&
            ComputerChoice == enChoice::Scissors) ||
           (PlayerChoice == enChoice::Scissors &&
            ComputerChoice == enChoice::Paper) ||
           (PlayerChoice == enChoice::Paper &&
            ComputerChoice == enChoice::Stone))
  {
    return enWinnerIs::Player;
  }
  else
  {

    return enWinnerIs::Computer;
  }
}

void PrintPlayersChoices(stGamePlayerData GamePlayersData)
{

  short PlayerChoice = GamePlayersData.PlayerInput;
  short ComputerChoice = GamePlayersData.ComputerInput;

  // Print Player choice
  if (PlayerChoice == enChoice::Stone)
    cout << "\nPlayer   Choice: Stone\n";
  else if (PlayerChoice == enChoice::Paper)
    cout << "\nPlayer   Choice: Paper\n";
  else
  {
    cout << "Player   Choice: Scissors\n";
  }

  // Print Player choice
  if (ComputerChoice == enChoice::Stone)
    cout << "Computer Choice :  Stone\n";
  else if (ComputerChoice == enChoice::Paper)
    cout << "Computer Choice : Paper\n";
  else
  {
    cout << "Computer Choice: Scissors\n";
  }

  // Print RoundWinner
  if (HowIsWinner(GamePlayersData) == enWinnerIs::Player)
  {
    cout << "\033[42mRound Winner   : [Player]\033[0m\n" << endl;

  }
  else if (HowIsWinner(GamePlayersData) == enWinnerIs::Computer)
  {
    cout << "\033[41mRound Winner   : [Computer]\033[0m\n\a" << endl;

   
  }
  else
  {
      cout << "\033[43mRound Winner   : [No Winner]\033[0m\n" << endl;

  }
}
short CountPoints(stGamePlayerData &GamePlayersData, short &HowIsWinner)
{

  if (HowIsWinner == enWinnerIs::Player)
  {

    return GamePlayersData.PlayerPoints++;
  }
  else if (HowIsWinner == enWinnerIs::Computer)
  {
    return GamePlayersData.ComputerPoints++;
  }
  else
  {
    return GamePlayersData.DrawTimes++;
  }

  return 0;
}

void StartRound(short &Rounds, stGamePlayerData &RoundData,stGamePlayerData &GamePlayersData)
{
  Rounds = AskAboutRounds();

  for (int i = 1; i <= Rounds; i++)
  {
    cout << "\nRound [" << i << "] begins:\n\n";

    RoundData = ReadPlayersChoices();

    cout << "\n____________________ Round [" << i << "] ____________________\n";

    PrintPlayersChoices(RoundData);

    cout << "__________________________________________________\n\n";
    
    short RoundWinner = HowIsWinner(RoundData);
    CountPoints(GamePlayersData, RoundWinner);
    
  }
}

string AddTabs()
{
  return "\t\t\t\t";
}

string AddLines()
{
  return "________________________________________________________________________________________";
}

string FinalWinnerIs(stGamePlayerData &GamePlayersData)
{
  if (GamePlayersData.ComputerPoints == GamePlayersData.PlayerPoints)
    return "\033[43mNoWinner\033[0m";
  else if (GamePlayersData.PlayerPoints > GamePlayersData.ComputerPoints)
    return "\033[42mPlayer\033[0m";
  else
  return "\033[41mComputer\033[0m\a";
}

void ShowGameOver(stGamePlayerData &GamePlayersData, short &Rounds)
{

  

  cout << AddTabs();
  cout << AddLines();

  cout << endl
       << endl;

  cout << AddTabs();
  cout << AddTabs();
  cout << "+++ Game Over +++" << AddTabs();

  cout << endl
       << endl;

  cout << AddTabs();
  cout << AddLines();

  cout << endl
       << endl;

  cout << AddTabs();
  cout << "_______________________________ [Game Results ]_________________________________________\n\n";

  cout << AddTabs() << "Game Rounds        : " << Rounds << endl;
  cout << AddTabs() << "Player won times   : " << GamePlayersData.PlayerPoints << endl;
  cout << AddTabs() << "Computer won times : " << GamePlayersData.ComputerPoints << endl;
  cout << AddTabs() << "Draw times         : " << GamePlayersData.DrawTimes << endl;
  string FinalWinner = FinalWinnerIs(GamePlayersData);
  cout << AddTabs() << "Final Winner       : " << FinalWinner << endl;

  cout << AddTabs();
  cout << AddLines();

  cout << endl
       << endl;

  cout << AddTabs();
}

void StartGame()
{
  char PlayAgain;
  do {
    stGamePlayerData RoundData;
    short Rounds = 0;
    // Rounds = AskAboutRounds();
    stGamePlayerData GamePlayersData;
    StartRound(Rounds, RoundData,GamePlayersData);
    ShowGameOver(GamePlayersData, Rounds);
    PlayAgain = AskAboutAgainGame();
  }while (PlayAgain == 'Y' || PlayAgain == 'y');

}



int main()
{

  srand((unsigned)time(NULL));
  StartGame();
  
  // ReadCharY_Or_N();
  return 0;
}
