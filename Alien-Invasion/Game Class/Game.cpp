#include "Game.h"
#include<iostream>
#include <iomanip>

using namespace std;

Game::Game()
{
	srand(time(0));
    pAlienArmy = new AlienArmy;
    pEarthArmy = new EarthArmy;
	pAllyArmy  = new AllyArmy;
	pRand = new RandGen(this);

	ESDead = ETDead = EGDead = HUDead = 0;
	ASDead = ADDead = AMDead = 0;

	Dfearth = Ddearth = Dbearth = 0;
	Dfalien = Ddalien = Dbalien = 0;

	HealedUnits = 0;
	InfectionProb = 0;
	TotalInfectedUnits = 0;
	CurrentInfectedUnits = 0;
	UMLInfectedUnits = 0;
	
	EndGame = false;
	SilentMode = false;
	CallAlly = false;
	AllyWithdraw = false;
	StartGame();
}

void Game::StartGame()
{
	//Asks the user for the name of the file and check its validity
	bool ValidName = false;
	cout << "	ALIEN INVASION ! " << endl
		<< "Please enter your File Parameters path" << endl;
	string Filename;
	while (!ValidName)
	{
		cin >> Filename;
		ValidName = LoadParameters(Filename + ".txt");
	}

	//Asks the user to choose between silent and iteractive modes
	char ans;
	cout << "Please select the program mode, Do you want interactive (I) or silent mode (S)? " << endl
		<< "(I/S)? ";
	cin >> ans;
	if (ans == 'S')
		SilentMode = true;


	if (SilentMode)
	{
		cout << "Silent Mode\n" << "Simulation Starts..\n";	
	}
	
	//Initialize output file
	SetOutFile();

	//Start the game
	MainLoop();

	//Print the game statistics in the output file
	GameStatistics();
	if (SilentMode)
	{
		cout << "Simulation ends, Output file is created\n";
	}
}

bool Game::LoadParameters(string Filename)
{
	ifstream Infile(Filename);
	if (Infile.is_open())
	{
		Inputs EarthParameters; // instance of struct for Earth Units
		Inputs AlienParameters;  // instance of struct for Alien Units
		Inputs AllyParameters; // instance of struct for Ally Units

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

		//Ally Ranges
		Infile >> AllyParameters.lower_power;
		Infile.ignore(1) >> AllyParameters.upper_power;


		Infile >> AllyParameters.lower_health;
		Infile.ignore(1) >> AllyParameters.upper_health;

		Infile >> AllyParameters.lower_capacity;
		Infile.ignore(1) >> AllyParameters.upper_capacity;

		//Infection probability
		Infile >> InfectionProb;

		Infile>>InfectionThreshold;         

		//set values for ranges and percentage
		pRand->SetEarthParameters(EarthParameters);
		pRand->SetAlienParameters(AlienParameters);
		pRand->SetAllyParameters(AllyParameters);

		Infile.close();
		return true;
	}
	else
	{
		cout << "ERROR, Please enter a valid file name. " << endl;
		return false;

	}
}

void Game::GenerateArmy(bool AllyArmy)
{
	Unit* newUnit = nullptr;
	if (!AllyArmy) {
		int A = (rand() % 100) + 1;
		if (A <= pRand->GetProb())   //Generating Army condition
		{
			if (pEarthArmy->GetID() < 1000) {
				// Generating Earth Army
				for (int i = 0; i < pRand->GetN(); i++)
				{
					newUnit = pRand->GenerateUnits(TimeStep, Earth);
					pEarthArmy->AddUnit(newUnit);
				}
			}
			else if(!SilentMode)
			{
				cout << "\033[0m WARNING!!! CAN'T GENERATE MORE EARTH UNITS\n";
			}
		}
		// Generating Alien Army
		A = (rand() % 100) + 1;

		if (A <= pRand->GetProb()) {
			bool Intofront = true;
			if (pAlienArmy->GetID() < 3000) {
				for (int i = 0; i < pRand->GetN(); i++)
				{
					newUnit = pRand->GenerateUnits(TimeStep, Alien);
					if (newUnit->getType() == alienDrone)
					{
						pAlienArmy->AddUnit(newUnit, Intofront);  // Each time step we add drones to front ,then back and so on.
						Intofront = !Intofront;
					}
					else
						pAlienArmy->AddUnit(newUnit);
				}
			}
			else if (!SilentMode)
			{
				cout << "\033[0m WARNING!!! CAN'T GENERATE MORE ALIEN UNITS\n";
			}
		}
	}
	else if (!AllyWithdraw && CallAlly) 
	{
		int A = (rand() % 100) + 1;
		if (A <= pRand->GetProb())   //Generating Army condition
		{
			if (pAllyArmy->GetID() < 4500) {
				// Generating Ally Army

				for (int i = 0; i < pRand->GetN(); i++)
				{
					newUnit = pRand->GenerateUnits(TimeStep, Ally);
					pAllyArmy->AddUnit(newUnit);
				}
			}
			else if(!SilentMode)
			{
				cout << "\033[0m WARNING!!! CAN'T GENERATE MORE ALLY UNITS\n";
			}
		}
	}

}

void Game::SetOutFile()
{
	//Initialize output file
	ofstream OutputFile;
	OutputFile.open("outFile.txt", ios::out);
	OutputFile << "Td\t\t\tID\t\t\tTa\t\t\tTj\t\t\tDf\t\t\tDd\t\t\tDb" << endl;
}

void Game::AddtoOutFile(Unit* killedUnit)
{
	ofstream OutputFile;
	OutputFile.open("outFile.txt", ios::app);
	if (OutputFile.is_open())
	{
		OutputFile << endl;
		OutputFile << killedUnit->getTd() << setw(12);   //Join Time
		OutputFile << killedUnit->getID() << setw(12);   //Unit's ID
		OutputFile << killedUnit->getTa() << setw(12);   //Unit's ID
		OutputFile << killedUnit->getTj() << setw(12);   //Destruction Time

		int Df = killedUnit->getTa() - killedUnit->getTj();
		int Dd = killedUnit->getTd() - killedUnit->getTa();
		int Db = killedUnit->getTd() - killedUnit->getTj();
		
		//Update DfTotal, DdTotal and DbTotal for earth army
		if (killedUnit->getType() == earthSoldier ||
			killedUnit->getType() == earthGunnery ||
			killedUnit->getType() == earthTank || 
			killedUnit->getType() == healUnit)
		{
			Dfearth += Df;
			Ddearth += Dd;
			Dbearth += Db;
		}
		else if (killedUnit->getType() == alienSoldier ||
			killedUnit->getType() == alienMonster ||
			killedUnit->getType() == alienDrone)
		{
			Dfalien += Df;
			Ddalien += Dd;
			Dbalien += Db;
		}

		//Print Df, Dd, Db of each unit
		OutputFile << Df << setw(12);     //First Attack Delay
		OutputFile << Dd<< setw(12);      //Destruction Delay
		OutputFile << Db << setw(12);     //Battle Time
	}
	OutputFile.close();
}

void Game::GameStatistics() const
{
	ofstream OutputFile;
	OutputFile.open("outFile.txt", ios::app);

	//calculate total earth alive and destructed units
	int TotalEunits = GetCount(earthSoldier) + GetCount(earthTank) + GetCount(earthGunnery) + GetCount(healUnit);
	int TotalEdestructed = EGDead + ESDead + ETDead + HUDead;

	//calculate total alien alive and destructed units
	int TotalAunits = GetCount(alienSoldier) + GetCount(alienMonster) + GetCount(alienDrone);
	int TotalAdestructed = ADDead + ASDead + AMDead;

	if (OutputFile.is_open())
	{
		
		//////////////////////////Earth Army/////////////////////////////////
		OutputFile << endl <<  "\nBattle Result: " << FinalResult << endl;

		OutputFile << endl << "For Earth army: " << endl;

		//Total number of each unit
		OutputFile << "Total number of each unit: " << endl;
		OutputFile << "ES: " << GetCount(earthSoldier) << "\t\t" 
			<< "ET: " << GetCount(earthTank) << "\t\t"
			<< "EG :" << GetCount(earthGunnery) << "\t\t" 
			<< "HU: " << GetCount(healUnit) << endl;

		//percentage of destructed units relative to their total
		OutputFile << "Percentage of destructed units relative to their total " << endl;
		OutputFile << "ES: ";
		OutputFile << ((GetCount(earthSoldier) == 0) ? 0 : (double(ESDead) / GetCount(earthSoldier))* 100) << "%"; 
		OutputFile << "\t\t ET: ";
		OutputFile << ((GetCount(earthTank) == 0) ? 0 : (double(ETDead) / GetCount(earthTank)) * 100) << "%";
		OutputFile << "\t\t EG: ";
		OutputFile << ((GetCount(earthGunnery) == 0) ? 0 : (double(EGDead) / GetCount(earthGunnery)) * 100) << "%";
		OutputFile << "\t\t HU: ";
		OutputFile << ((GetCount(healUnit) == 0) ? 0 : (double(HUDead) / GetCount(healUnit)) * 100) << "%" << endl;


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
		OutputFile << ((TotalEunits == 0) ? 0 : (double(HealedUnits) / TotalEunits) * 100) << "%" << endl;

		//Percentage of units that where infected relative to total earth units
		OutputFile << "Infected units Percentage : ";
		OutputFile << ((TotalEunits == 0) ? 0 : (double(TotalInfectedUnits) / TotalEunits) * 100) << "%";

		//////////////////////////Alien Army/////////////////////////////////
		OutputFile << endl << "For Alien army: " << endl;
		OutputFile << "Total number of each unit: " << endl;
		OutputFile << "AS: " << GetCount(alienSoldier) << "\t\t AM: " <<
			GetCount(alienMonster) << "\t\t AD: " << GetCount(alienDrone) << endl;

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

	//if no earth units exist and alien has at least one unit, earth army loss the game
	if (E_total == 0 && A_Total > 0)
	{
		FinalResult = "loss";
		EndGame = true;	
		return;
	}

	//if no alien units exist and earth has at least one unit, earth army win the game
	else if (E_total > 0 && A_Total ==0)
	{
		FinalResult = "win";
		EndGame = true;
		return;
	}
	
	// if only remain in the two armies two unit types that cannot attack each other, 
	// or all units are dead in both armies consider it as a tie
	else if ((E_total == pEarthArmy->GetEScount() && A_Total == pAlienArmy->GetADcount()) 
		|| (E_total == pEarthArmy->GetEGcount() && A_Total == pAlienArmy->GetAScount())
		|| (E_total == 0 && A_Total == 0))
	{
		FinalResult = "tie";
		EndGame = true;
	}
}

int Game::GetCount(UnitType Unit_Type) const
{
	switch (Unit_Type)
	{
	case earthSoldier:
		return pEarthArmy->GetEScount() + ESDead + UMLsolider.getCount();
	case earthGunnery:
		return pEarthArmy->GetEGcount() + EGDead;
	case earthTank:
		return pEarthArmy->GetETcount() + ETDead + UMLtanks.getCount();
	case healUnit:
		return  pEarthArmy->GetHUcount() + HUDead;
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

void Game::DestroyUML()
{
	if (FinalResult == "loss" || FinalResult == "tie") {
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
		if (CallAlly && !AllyWithdraw)
		{
			CheckAllyWithdraw();
		}
	}
}

int Game::getInfectionProb() const
{
	return InfectionProb;
}

void Game::IncrementInfectedCount()
{
	CurrentInfectedUnits++;
	TotalInfectedUnits++;
}

void Game::DecrementInfectedCount()
{
	if(CurrentInfectedUnits)
		CurrentInfectedUnits--;
	if (UMLInfectedUnits)
		UMLInfectedUnits--;
}

void Game::CheckAllyWithdraw()
{
	if (CurrentInfectedUnits == 0)
	{
		Unit* destroyedUnit = nullptr;
		while(pAllyArmy->GetSUcount() > 0)  //destroy ally army and add them to killed list
		{
			destroyedUnit = pAllyArmy->removeUnit();
			destroyedUnit->setTa(TimeStep);
			AddtoKilledList(destroyedUnit);
		}
		AllyWithdraw = true;  //set it true so randgen won't generate ally army again
	}
}

bool Game::GetCallAlly() const
{
	return CallAlly;
}

void Game::MainLoop()
{
	while (!EndGame) //will stop when the game ends
	{
		////////////////////Check end of the game///////////////////////

		if (TimeStep > 40)
			CheckResult();   //check the game result each time step when time steps exceeded 40

		//at the end of the game destroy the uml if loss/tie
		if (EndGame)
		{
			DestroyUML();
			break;
		}

		//////////////////////Army Generation//////////////////////////

		GenerateArmy();   //generate units for two armies each time step

		//////////////////////////Printing/////////////////////////////

		if (!SilentMode)  //check that the game mode is not silent mode
		{
			PrintAliveUnits();
			cout << "\033[1;31m============== Killed/Destructed Units ==============" << endl;
		    PrintKilledList();
			cout << "\u001b[35m============== UML ==============" << endl;
			PrintUMLList();
			cout << "============== Attack Round ==============" << endl;
		}

		///////////////Attack Round//////////////////
		 pEarthArmy->Attack();    //Earth Army start attacking
		 SpreadInfectedUnits();   //infected ES spread infection

		 if(!CallAlly && !AllyWithdraw) 
		 {
			 if ((pEarthArmy->GetEScount() + UMLsolider.getCount()))
			 {
				 //check that infected percentage is greater than threshold
				 if ((double(CurrentInfectedUnits) / (pEarthArmy->GetEScount() + UMLsolider.getCount()) * 100) >= InfectionThreshold)
				 {
					 CallAlly = true;   //flag to call ally army
				 }
			 }
		 }
		 else if(CallAlly && !AllyWithdraw)
		 {
             GenerateArmy(true);   // to generate SU ONLY
			 pAllyArmy->Attack();  // Ally Army start attacking
			 CheckAllyWithdraw();  // check No of infected units each time step
		 }

		 pAlienArmy->Attack();  //Alien Army start attacking
		

		if (!SilentMode)
		{
			cout << "============== Units after attack round ==============" << endl;
			PrintAliveUnits();
			cout << "\n\033[1;31m============== Killed/Destructed Units ==============" << endl;
			PrintKilledList();
			cout << "\u001b[35m============== UML ==============" << endl;
			PrintUMLList();
			cout << "\u001b[32m=========================================" << endl;
			cout << "Infection percentage = " << ((pEarthArmy->GetEScount() + UMLsolider.getCount() == 0) ? 0 
				: double(CurrentInfectedUnits) / (pEarthArmy->GetEScount() + UMLsolider.getCount()) * 100) << "%";
			cout << endl;
			system("pause");
		}
		TimeStep++;  //increment time step
	}
}
	
void Game::AddtoKilledList(Unit* army)
{
	army->setTd(TimeStep);  //sets destruction time for the army 

	if(KilledList.enqueue(army));
	    AddtoOutFile(army);  //print killed unit's info in the output file

	//increment total dead counts of each unit
	switch (army->getType())
	{
	case earthSoldier:
		if(army->InfectedBefore()) CurrentInfectedUnits--;
		ESDead++;
		break;
	case earthGunnery:
		EGDead++;
		break;
	case earthTank:
		ETDead++;
		break;
	case healUnit:
		HUDead++;
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
	case saverUnit:
		break;
	}
}

void Game::AddtoUML(Unit* unit)
{
	if (unit->getType() == earthSoldier)
	{
		UMLsolider.enqueue(unit, unit->getESPriorty());

		if(unit->InfectedBefore())  //if unit is infected increment uml infected units count
			UMLInfectedUnits++;
	}
	else
		UMLtanks.enqueue(unit);

	if (!unit->checkUML())  //checks if the unit is in uml or not, to set its time only once  
	{
		unit->setTH(TimeStep);
	}
}

bool Game::UMLisEmpty() const
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

AlienArmy* Game::GetAlienArmyPtr() const
{
	return pAlienArmy;
}

EarthArmy* Game::GetEarthArmyPtr() const
{
	return pEarthArmy;
}

AllyArmy* Game::GetAllyArmyPtr() const
{
	return pAllyArmy;
}

RandGen* Game::GetRandGenPtr() const
{
	return pRand;
}

Unit* Game::GetEnemiesUnit(ArmyType Army_Type, UnitType Unit_Type,bool BackDrone) const
{
	//get unit from its list to be attacked 
	Unit* unit2 = nullptr;
	switch (Army_Type)
	{
	case Earth:
	{
		unit2 = pEarthArmy->removeUnit(Unit_Type);
	}
	break;
	case Alien:
		unit2 = pAlienArmy->removeUnit(Unit_Type, BackDrone);
		break;
	case Ally:
		unit2 = pAllyArmy->removeUnit();
	default:
		break;
	}
	return unit2;
}

int Game::GetCurrentTime() const
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

void Game::SpreadInfectedUnits()
{
	//spread infection of earth army
	LinkedQueue <Unit*> InfectedUnitsFromES;
	for (int i = 0; i < CurrentInfectedUnits - UMLInfectedUnits; i++)
	{
		Unit* infectedUnit;
		if (pEarthArmy->SpreadInfection(infectedUnit))   //if there is an infected unit
		{
			IncrementInfectedCount();   //incrementing the no of  infected units
			InfectedUnitsFromES.enqueue(infectedUnit);  // storing infected units to print them
		}
	}

	if (!SilentMode && !InfectedUnitsFromES.isEmpty())  //printing infected units from ES
	{
		cout << "ES Infected by infected ES [";
		InfectedUnitsFromES.print();
		cout << " ]" << endl;
	}

	Unit* infectedUnit;
	while (InfectedUnitsFromES.dequeue(infectedUnit));
}

void Game::PrintFight(Unit* shooter, LinkedQueue<Unit*> fightingUnits, bool InfectionList) const
{
	if (!SilentMode)
	{
		string type;
		switch (shooter->getType())
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
		case healUnit:
			type = "HU";
			break;
		case saverUnit:
			type = "SU";
			break;
		}
		cout << type << " ";
		if (shooter->InfectedBefore())  cout << "*";
		cout << shooter->getID();

		if (InfectionList)
			cout << " infects [";
		else if (type == "HU")
			cout << " heals [";
		else
			cout << " shots [";
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
	cout << "\033[1;36m============== Ally Army Alive Units ==============" << endl;
	pAllyArmy->Print();
	cout << endl;
}

Game::~Game()
{
	Unit* KilledUnit = nullptr;
	while (!KilledList.isEmpty())
	{
		KilledList.dequeue(KilledUnit);
		delete KilledUnit;
	}

	delete pEarthArmy;
	delete pAlienArmy;
	delete pAllyArmy;
	delete pRand;
}

