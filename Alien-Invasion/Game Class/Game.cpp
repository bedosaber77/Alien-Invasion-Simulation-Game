#include "Game.h"
#include<iostream>
using namespace std;

Game::Game()
{
	srand(time(0));
    pAlienArmy = new AlienArmy;
    pEarthArmy = new EarthArmy;
	pRand = new RandGen(this);

	EScount = EGcount = ETcount = AScount = ADcount = AMcount = 0;

	ESDead = ETDead = EGDead = 0;
	ASDead = ADDead = AMDead = 0;

	Dfearth = Ddearth = Dbearth = 0;
	Dfalien = Ddalien = Dbalien = 0;
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
		OutputFile << killedUnit->getTd() << "\t\t\t";   //Join Time
		OutputFile << killedUnit->getID() << "\t\t\t";   //Unit's ID
		OutputFile << killedUnit->getTj() << "\t\t\t";  //Destruction Time
		
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
		OutputFile << killedUnit->getTa() - killedUnit->getTj()  << "\t\t\t";     //First Attack Delay
		OutputFile << killedUnit->getTd() - killedUnit->getTa() << "\t\t\t";      //Destruction Delay
		OutputFile << killedUnit->getTd() - killedUnit->getTj() << "\t\t\t";      //Battle Time
	}
	OutputFile.close();
}

void Game::GameStatistics()
{
	ofstream OutputFile;
	OutputFile.open("outFile.txt", ios::app);

	if (OutputFile.is_open())
	{
		//Total number of each unit
		
		//int EScount, EGcount, ETcount, AScount, ADcount, AMcount;
		//pRand->GetUnitsNo(EScount, EGcount, ETcount, AScount, ADcount, AMcount);
		
		//////////////////////////Earth Army/////////////////////////////////

		OutputFile << endl << "For Earth army: " << endl;

		//Total number of each unit
		OutputFile << "Total number of each unit: " << endl;
		OutputFile << "ES: " << EScount << "\t\t ET: " << ETcount << "\t\t EG: " << EGcount << endl;

		//percentage of destructed units relative to their total
		OutputFile << "Percentage of destructed units relative to their total " << endl;
		OutputFile << "ES: " << ESDead / double(EScount) * 100 << "%";
		OutputFile << "\t\t ET: " << ETDead / double(ETcount) * 100 << "%"; 
		OutputFile << "\t\t EG: " << EGDead / double(EGcount) * 100 << "%" << endl;

		// Percentage of destructed units relative to total units
		OutputFile << "Percentage of destructed units relative to total units: ";
		OutputFile << double(ESDead + EGDead + ETDead) / (EScount + ETcount + EGcount) * 100 << "%" << endl;

		//Average of Df
		OutputFile << "Average of Df: ";
		OutputFile << double(Dfearth) / (ESDead + EGDead + ETDead) << endl;

		//Average of Dd
		OutputFile << "Average of Dd: ";
		OutputFile << double(Ddearth) / (ESDead + EGDead + ETDead) << endl;

		//Average of Db
		OutputFile << "Average of Db: ";
		OutputFile << double(Dbearth) / (ESDead + EGDead + ETDead) << endl;

		//Df/Db%
		OutputFile << "Df/Db: ";
		OutputFile << double(Dfearth) / Dbearth * 100 << "%" << endl;

		//Dd%Db
		OutputFile << "Dd/Db: ";
		OutputFile << double(Ddearth) / Dbearth * 100 << "%" << endl;

		//////////////////////////Alien Army/////////////////////////////////
		OutputFile << endl << "For Alien army: " << endl;
		OutputFile << "Total number of each unit: " << endl;
		OutputFile << "AS: " << AScount << "\t\t AM: " << AMcount << "\t\t AD: " << ADcount << endl;

		//percentage of destructed units relative to their total
		OutputFile << "Percentage of destructed units relative to their total " << endl;
		OutputFile << "AS: " << ASDead / double(AScount) * 100 << "%";
		OutputFile << "\t\t AM: " << AMDead / double(AMcount) * 100 << "%";
		OutputFile << "\t\t AD: " << ADDead / double(ADcount) * 100 << "%" << endl;

		// Percentage of destructed units relative to total units
		OutputFile << "Percentage of destructed units relative to total units: ";
		OutputFile << double(ASDead + AMDead + ADDead) / (AScount + AMcount + ADcount) * 100 << "%" << endl;

		//Average of Df
		OutputFile << "Average of Df: ";
		OutputFile << double(Dfalien) / (ASDead + AMDead + ADDead) << endl;

		//Average of Dd
		OutputFile << "Average of Dd: ";
		OutputFile << double(Ddalien) / (ASDead + AMDead + ADDead) << endl;

		//Average of Db
		OutputFile << "Average of Db: ";
		OutputFile << double(Dbalien) / (ASDead + AMDead + ADDead) << endl;

		//Df/Db%
		OutputFile << "Df/Db: ";
		OutputFile << double(Dfalien) / Dbalien * 100 << "%" << endl;

		//Dd%Db
		OutputFile << "Dd/Db: ";
		OutputFile << double(Ddalien) / Dbalien * 100 << "%" << endl;

	}
	OutputFile.close();
}

ArmyType Game::GameWinner()
{
	if (pAlienArmy->getCount() == 0 && pEarthArmy->getCount() != 0)
		return Earth;

	if (pEarthArmy->getCount() == 0 && pAlienArmy->getCount() != 0)
		return Alien;
}

void Game::UpdateCounts(ArmyType armyType, Unit* unit)
{
	switch (armyType)
	{
	case Earth:
	{
		switch (unit->getType())
		{
		case earthSoldier:
			EScount++;
		  break;
		case earthGunnery:
			EGcount++;
		  break;
		case earthTank:
			ETcount++;
			break;
		}	
	}
	break;
	case Alien:
	{
		switch (unit->getType())
		{
		case alienSoldier:
			AScount++;
		  break;
		case alienMonster:
			AMcount++;
		  break;
		case alienDrone:
			ADcount++;
		  break;
		}
	}
	break;
	default:
		break;
	}
}

void Game::MainLoop()
{
	while (TimeStep <= 40) //will stop when it completes 50 time steps for now (phase 1)
	{
		Unit* newUnit = nullptr;
		int A = (rand() % 100) + 1;
		if (A <= pRand->GetProb())   //Generating Army condition
		{
			// Generating Earth Army
			for (int i = 0; i < pRand->GetN(); i++)
			{
				newUnit = pRand->GenerateUnits(TimeStep, Earth);
				pEarthArmy->AddUnit(newUnit);
				UpdateCounts(Earth, newUnit);
			}
		}
			// Generating Alien Army
		A = (rand() % 100) + 1;
			if (A <= pRand->GetProb()){
			for (int i = 0; i < pRand->GetN(); i++)
			{
				newUnit = pRand->GenerateUnits(TimeStep, Alien);
				pAlienArmy->AddUnit(newUnit, i % 2);
				UpdateCounts(Alien, newUnit);
			}
		}
		//	cout << "============== Units fighting at current step ==============" << endl;
			PrintAliveUnits();
			//cout << "============== Units fighting at current step ==============" << endl;
			cout << "\033[1;31m============== Killed/Destructed Units ==============" << endl;
			PrintKilledList();
			//cout << "============== Units fighting at current step ==============" << endl;
			pEarthArmy->Attack();
			pAlienArmy->Attack();
			cout << "============== Units after attack round ==============" << endl;
			PrintAliveUnits();
			cout << "\n\033[1;31m============== Killed/Destructed Units ==============" << endl;
			PrintKilledList();
			cout << "\u001b[35m============== UML ==============" << endl;
			PrintUMLList();
			cout << endl;
			system("pause");
			TimeStep++;
		}
}
	

void Game::AddtoKilledList(Unit* army)
{
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
		if (!Healedbefore)
			pEarthArmy->incHealedUnits();
		
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

void Game::PrintFight(Unit* shooter, UnitType shooterType,LinkedQueue<Unit*> fightingUnits)
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

