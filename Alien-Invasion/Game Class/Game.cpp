#include "Game.h"
#include<iostream>
#include <iomanip>
using namespace std;

Game::Game()
{
	srand(time(0));
    pAlienArmy = new AlienArmy;
    pEarthArmy = new EarthArmy;
	pRand = new RandGen(this);

	ESDead = ETDead = EGDead = 0;
	ASDead = ADDead = AMDead = 0;

	Dfearth = Ddearth = Dbearth = 0;
	Dfalien = Ddalien = Dbalien = 0;

	HealedUnits = 0;
	EndGame = false;
	StartGame();
}

void Game::StartGame()
{
	bool ValidName = false;
	cout << "	ALIEN INVASION ! " << endl
		<< "Please enter your File Parameters path" << endl;
	string Filename;
	while (!ValidName)
	{
		cin >> Filename;
		ValidName = LoadParameters(Filename + ".txt");
	}
	//Ask for silent mood
	char ans;
	cout << "Please select the program mode, Do you want interactive (I) or silent mode (S)? " << endl
		<< "(I/S)? ";
	cin >> ans;
	if (ans == 'S')
		SilentMood = true;


	if (SilentMood)
	{
		cout << "Silent Mode\n" << "Simulation Starts..\n"
			<< "Simulation ends, Output file is created\n";
	}
	
	//Initialize output file
	SetOutFile();
	MainLoop();
	GameStatistics();
}

bool Game::LoadParameters(string Filename)
{
	ifstream Infile(Filename);
	if (Infile.is_open())
	{
		Inputs EarthParameters; // instance of struct for Earth Units
		Inputs AlienParameters;  // instance of struct for Army Units


		//Number of units for each army
		int N;
		Infile >> N;
		pRand->SetN(N);


		Infile >> EarthParameters.ESpercent >> EarthParameters.ETpercent >> EarthParameters.EGpercent>>EarthParameters.HUpercent;

		if (EarthParameters.HUpercent > 5)
		{
			EarthParameters.HUpercent = 5;	//maximum it can be
		}
		Infile >> AlienParameters.ASpercent >> AlienParameters.AMpercent >> AlienParameters.ADpercent;

		// Probability
		int Prob;
		Infile >> Prob;
		pRand->SetProb(Prob);



		// Earth Ranges
		Infile >> EarthParameters.lower_power;
		Infile.ignore(1) >> EarthParameters.upper_power;


		Infile >> EarthParameters.lower_health;
		Infile.ignore(1) >> EarthParameters.upper_health;

		Infile >> EarthParameters.lower_capacity;
		Infile.ignore(1) >> EarthParameters.upper_capacity;



		//Alien Ranges
		Infile >> AlienParameters.lower_power;
		Infile.ignore(1) >> AlienParameters.upper_power;


		Infile >> AlienParameters.lower_health;
		Infile.ignore(1) >> AlienParameters.upper_health;

		Infile >> AlienParameters.lower_capacity;
		Infile.ignore(1) >> AlienParameters.upper_capacity;



		//set values for ranges and percentage
		pRand->SetEarthParameters(EarthParameters);
		pRand->SetAlienParameters(AlienParameters);

		Infile.close();
		return true;
	}
	else
	{
		cout << "ERROR, Please enter a valid file name. " << endl;
		return false;

	}
}

void Game::SetOutFile()
{
	//Initialize output file
	ofstream OutputFile;
	OutputFile.open("outFile.txt", ios::out);
	OutputFile << "Td\t\t\tID\t\t\tTj\t\t\tDf\t\t\tDd\t\t\tDb" << endl;
}

//Function that adds killed unit to the output file
void Game::AddtoOutFile(Unit* killedUnit)
{
	//string outFile;
	ofstream OutputFile;
	OutputFile.open("outFile.txt", ios::app);
	if (OutputFile.is_open())
	{
		OutputFile << endl;
		OutputFile << killedUnit->getTd() << setw(12);   //Join Time
		OutputFile << killedUnit->getID() << setw(12);   //Unit's ID
		OutputFile << killedUnit->getTj() << setw(12);  //Destruction Time
		
		//Update DfTotal, DdTotal and DbTotal for earth army
		if (killedUnit->getType() == earthSoldier || killedUnit->getType() == earthGunnery || killedUnit->getType() == earthTank)
		{
			Dfearth += killedUnit->getTa() - killedUnit->getTj();
			Ddearth += killedUnit->getTd() - killedUnit->getTa();
			Dbearth += killedUnit->getTd() - killedUnit->getTj();
		}
		else if (killedUnit->getType() == alienSoldier || killedUnit->getType() == alienMonster || killedUnit->getType() == alienDrone)
		{
			Dfalien += killedUnit->getTa() - killedUnit->getTj();
			Ddalien += killedUnit->getTd() - killedUnit->getTa();
			Dbalien += killedUnit->getTd() - killedUnit->getTj();
		}

		//Print Df, Dd, Db of each unit
		OutputFile << killedUnit->getTa() - killedUnit->getTj()  << setw(12);     //First Attack Delay
		OutputFile << killedUnit->getTd() - killedUnit->getTa() << setw(12);      //Destruction Delay
		OutputFile << killedUnit->getTd() - killedUnit->getTj() << setw(12);      //Battle Time
	}
	OutputFile.close();
}

void Game::GameStatistics()
{
	ofstream OutputFile;
	OutputFile.open("outFile.txt", ios::app);

	int TotalEunits = GetCount(earthSoldier) + GetCount(earthTank) + GetCount(earthGunnery);
	int TotalEdestructed = EGDead + ESDead + ETDead;

	int TotalAunits = GetCount(alienSoldier) + GetCount(alienMonster) + GetCount(alienDrone);
	int TotalAdestructed = ADDead + ASDead + AMDead;

	if (OutputFile.is_open())
	{
		//////////////////////////Earth Army/////////////////////////////////
		OutputFile << "\nBattle Result: " << FinalResult << endl;

		OutputFile << endl << "For Earth army: " << endl;

		//Total number of each unit
		OutputFile << "Total number of each unit: " << endl;
		OutputFile << "ES: " << GetCount(earthSoldier) << "\t\t" 
			<< "ET: " << GetCount(earthTank) << "\t\t"
			<< "EG : " << GetCount(earthGunnery) << endl;

		//percentage of destructed units relative to their total
		OutputFile << "Percentage of destructed units relative to their total " << endl;
		OutputFile << "ES: ";
		OutputFile << ((GetCount(earthSoldier) == 0) ? 0 : (double(ESDead) / GetCount(earthSoldier))* 100) << "%";  //if No earth soldiers generated print 0
		OutputFile << "\t\t ET: ";
		OutputFile << ((GetCount(earthTank) == 0) ? 0 : (double(ETDead) / GetCount(earthTank)) * 100) << "%";
		OutputFile << "\t\t EG: ";
		OutputFile << ((GetCount(earthGunnery) == 0) ? 0 : (double(EGDead) / GetCount(earthGunnery)) * 100) << "%" << endl;

		// Percentage of destructed units relative to total units
		OutputFile << "Percentage of destructed units relative to total units: ";
		OutputFile << ((TotalEunits == 0) ? 0 : (double(TotalEdestructed) / TotalEunits) * 100) << "%" << endl;

		//Average of Df
		OutputFile << "Average of Df: ";
		OutputFile << ((TotalEdestructed == 0) ? 0 : double(Dfearth) / TotalEdestructed) << endl;

		//Average of Dd
		OutputFile << "Average of Dd: ";
		OutputFile << ((TotalEdestructed == 0) ? 0 : double(Ddearth) / TotalEdestructed) << endl;

		//Average of Db
		OutputFile << "Average of Db: ";
		OutputFile << ((TotalEdestructed == 0) ? 0 : double(Dbearth) / TotalEdestructed) << endl;

		//Df/Db%
		OutputFile << "Df/Db: ";
		OutputFile << ((Dbearth == 0)? 0 : (double(Dfearth) / Dbearth) * 100) << "%" << endl;

		//Dd%Db
		OutputFile << "Dd/Db: ";
		OutputFile << ((Dbearth == 0) ? 0 : (double(Ddearth) / Dbearth) * 100) << "%" << endl;

		//Percentage of units healed successfully relative to total earth units
		OutputFile << "Healed units Percentage: ";
		OutputFile << ((TotalEunits == 0) ? 0 : (double(HealedUnits) / TotalEunits) * 100) << "%";

		//////////////////////////Alien Army/////////////////////////////////
		OutputFile << endl << "For Alien army: " << endl;
		OutputFile << "Total number of each unit: " << endl;
		OutputFile << "AS: " << GetCount(alienSoldier) << "\t\t AM: " << GetCount(alienMonster) << "\t\t AD: " << GetCount(alienDrone) << endl;

		//percentage of destructed units relative to their total
		OutputFile << "Percentage of destructed units relative to their total " << endl;
		OutputFile << "AS: ";
		OutputFile << ((GetCount(alienSoldier) == 0) ? 0 : (double(ASDead) / GetCount(alienSoldier)) * 100) << "%";
		OutputFile << "\t\t AM: ";
		OutputFile << ((GetCount(alienMonster) == 0) ? 0 : (double(AMDead) / GetCount(alienMonster)) * 100) << "%";
		OutputFile << "\t\t AD: ";
		OutputFile << ((GetCount(alienDrone) == 0) ? 0 : (double(ADDead) / GetCount(alienDrone)) * 100) << "%" << endl;

		// Percentage of destructed units relative to total units
		OutputFile << "Percentage of destructed units relative to total units: ";
		OutputFile << ((TotalAunits == 0) ? 0 : (double(TotalAdestructed) / TotalAunits) * 100) << "%" << endl;

		//Average of Df
		OutputFile << "Average of Df: ";
		OutputFile << ((TotalAdestructed == 0) ? 0 : double(Dfalien) / TotalAdestructed) << endl;

		//Average of Dd
		OutputFile << "Average of Dd: ";
		OutputFile << ((TotalAdestructed == 0) ? 0 : double(Ddalien) / TotalAdestructed) << endl;

		//Average of Db
		OutputFile << "Average of Db: ";
		OutputFile << ((TotalAdestructed == 0) ? 0 : double(Dbalien) / TotalAdestructed) << endl;

		//Df/Db%
		OutputFile << "Df/Db: ";
		OutputFile << ((Dbalien == 0) ? 0 : (double(Dfalien) / Dbalien) * 100) << "%" << endl;

		//Dd%Db
		OutputFile << "Dd/Db: ";
		OutputFile << ((Dbalien == 0) ? 0 : (double(Ddalien) / Dbalien) * 100) << "%" << endl;

	}
	OutputFile.close();
}

void Game::CheckResult()
{
	int E_total = pEarthArmy->GetEScount() + pEarthArmy->GetEGcount() + pEarthArmy->GetETcount();
	int A_Total = pAlienArmy->GetAScount() + pAlienArmy->GetAMcount() + pAlienArmy->GetADcount();
		if (E_total == 0 && A_Total > 0)
		{
			FinalResult = "loss";
			EndGame = true;	
			return;
		}

		else if (E_total > 0 && A_Total ==0)
		{
			FinalResult = "win";
			EndGame = true;
			return;
		}
	
		//if both attacked successfully, continue the game
		
		else if ((E_total == pEarthArmy->GetEScount() && A_Total == pAlienArmy->GetADcount()) 
			|| (E_total == pEarthArmy->GetEGcount() && A_Total == pAlienArmy->GetAScount())
			|| (E_total == 0 && A_Total == 0))
		{
			FinalResult = "tie";
			EndGame = true;
		}
		/*else if (pEarthArmy->Attack() && !pAlienArmy->Attack() && pAlienArmy->GetAScount() + pAlienArmy->GetAMcount() + pAlienArmy->GetADcount() == 0)
			FinalResult = win;
		else if (!pEarthArmy->Attack() && pAlienArmy->Attack() &&
			pEarthArmy->GetEScount() + pEarthArmy->GetEGcount() + pEarthArmy->GetETcount() == 0)
			FinalResult = loss;*/
}


int Game::GetCount(UnitType Unit_Type)
{
	switch (Unit_Type)
	{
	case earthSoldier:
		return pEarthArmy->GetEScount() + ESDead + UMLsolider.getCount();
	case earthGunnery:
		return pEarthArmy->GetEGcount() + EGDead;
	case earthTank:
		return pEarthArmy->GetETcount() + ETDead + UMLtanks.getCount();
	case alienSoldier:
		return pAlienArmy->GetAScount() + ASDead;
	case alienMonster:
		return pAlienArmy->GetAMcount() + AMDead;
	case alienDrone:
		return pAlienArmy->GetADcount() + ADDead;
	default:
		break;
	}
}

void Game::UpdateHealCount()
{
	HealedUnits++;
}

void Game::MainLoop()
{
	while (!EndGame) //will stop when it completes 50 time steps for now (phase 1)
	{
		if (TimeStep >= 40)
			CheckResult();
		if (EndGame)
		{
			Unit* dummy;
			int dumm;
			while (UMLsolider.dequeue(dummy, dumm))
			{
				AddtoKilledList(dummy);
			}
			while (UMLtanks.dequeue(dummy))
			{
				AddtoKilledList(dummy);
			}
			break;
		}
		Unit* newUnit = nullptr;
		int A = (rand() % 100) + 1;
		if (A <= pRand->GetProb() && pEarthArmy->GetID()<2000)   //Generating Army condition
		{
			// Generating Earth Army
			for (int i = 0; i < pRand->GetN(); i++)
			{
				newUnit = pRand->GenerateUnits(TimeStep, Earth);
				pEarthArmy->AddUnit(newUnit);
			}
		}
			// Generating Alien Army
		    A = (rand() % 100) + 1;
			if (A <= pRand->GetProb() && pAlienArmy->GetID()<4000){
			for (int i = 0; i < pRand->GetN(); i++)
			{
				newUnit = pRand->GenerateUnits(TimeStep, Alien);
				pAlienArmy->AddUnit(newUnit, i % 2);
			}
		}
		
		

			if (!SilentMood)
			{
				PrintAliveUnits();
				cout << "\033[1;31m============== Killed/Destructed Units ==============" << endl;
				PrintKilledList();
				cout << "============== Attack Round ==============" << endl;
			}

			bool EarthAT = pEarthArmy->Attack(); //Discuss if it is needed
			bool AlienAT = pAlienArmy->Attack();
			/*
			if (!EarthAT && !AlienAT && TimeStep >= 40)
			{
				FinalResult = "tie";
				EndGame = true;
			}
			*/

			if (!SilentMood)
			{
				cout << "============== Units after attack round ==============" << endl;
				PrintAliveUnits();
				cout << "\n\033[1;31m============== Killed/Destructed Units ==============" << endl;
				PrintKilledList();
				cout << "\u001b[35m============== UML ==============" << endl;
				PrintUMLList();
				cout << endl;
				system("pause");
			}
			TimeStep++;
		}
}
	
void Game::AddtoKilledList(Unit* army)
{
	army->setTd(TimeStep);
	KilledList.enqueue(army);
	AddtoOutFile(army);
	switch (army->getType())
	{
	case earthSoldier:
		ESDead++;
		break;
	case earthGunnery:
		EGDead++;
		break;
	case earthTank:
		ETDead++;
		break;
	case alienSoldier:
		ASDead++;
		break;
	case alienMonster:
		AMDead++;
		break;
	case alienDrone:
		ADDead++;
		break;
	}
}

void Game::ClearKilledList()
{
	Unit* KilledUnit;
	while (!KilledList.isEmpty())
	{
		KilledList.dequeue(KilledUnit);
		delete KilledUnit;
	}
}

void Game::AddtoUML(Unit* unit)
{
	if (unit->getType() == earthSoldier)
		UMLsolider.enqueue(unit, unit->getESPriorty());
	else
		UMLtanks.enqueue(unit);

	bool Healedbefore;
	if (!unit->checkUML(Healedbefore)) 
	{

		unit->setTH(TimeStep);
	}
}

bool Game::UMLisEmpty()
{
	return UMLsolider.isEmpty() && UMLtanks.isEmpty();
}

Unit* Game::getUnitToHeal()
{
	Unit* unit=nullptr;
	int pri;
	if (!UMLsolider.isEmpty())
		UMLsolider.dequeue(unit, pri);
	else if (!UMLtanks.isEmpty())
		UMLtanks.dequeue(unit);
	return unit;
}

AlienArmy* Game::GetAlienArmyPtr()
{
	return pAlienArmy;
}

EarthArmy* Game::GetEarthArmyPtr()
{
	return pEarthArmy;
}

RandGen* Game::GetRandGenPtr()
{
	return pRand;
}

Unit* Game::GetEnemiesUnit(ArmyType Army_Type, UnitType Unit_Type,bool BackDrone)
{
	Unit* unit2 = nullptr;
	switch (Army_Type)
	{
	case Earth:
	{
		unit2 = pEarthArmy->removeUnit(Unit_Type);
	}
	break;
	case Alien:
		unit2 = pAlienArmy->removeUnit(Unit_Type, BackDrone );

		break;
	default:
		break;
	}
	return unit2;

}

int Game::GetCurrentTime()
{
	return TimeStep;
}

void Game::PrintKilledList() const
{
	
	cout << KilledList.getCount() << " units [";
	KilledList.print();
	cout << " ] \n\033[0m";

}

void Game::PrintUMLList() const
{
	cout << UMLsolider.getCount() << " UMLsolider [";
	UMLsolider.print();
	cout << " ] \n\u001b[35m";
	cout << UMLtanks.getCount() << " UMLtanks [";
	UMLtanks.print();
	cout << " ] \n\033[0m";
	
}

void Game::PrintFight(Unit* shooter, UnitType shooterType,LinkedQueue<int> fightingUnits)
{
	if (!SilentMood)
	{
		string type;
		switch (shooterType)
		{
		case earthSoldier:
			type = "ES";
			break;
		case earthGunnery:
			type = "EG";
			break;
		case earthTank:
			type = "ET";
			break;
		case alienSoldier:
			type = "AS";
			break;
		case alienMonster:
			type = "AM";
			break;
		case alienDrone:
			type = "AD";
			break;
		}
		cout << type << " " << shooter->getID() << " shots [";
		fightingUnits.print();
		cout << "]" << endl;
	}
	
}

void Game::PrintAliveUnits() const
{
	cout << "Current Timestep " << TimeStep << endl;
	cout << "\033[1;36m============== Earth Army Alive Units ==============" << endl;
	pEarthArmy->Print();
	cout << endl;
	cout << "\n\033[1;32m============== Alien Army Alive Units ==============" << endl;
	pAlienArmy->Print();
	cout << endl;
	cout << "\n\033[0m";
}

Game::~Game()
{
	ClearKilledList();
	delete pEarthArmy;
	delete pAlienArmy;
	delete pRand;
}

