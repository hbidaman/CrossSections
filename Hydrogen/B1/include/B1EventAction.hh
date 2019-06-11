//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1EventAction.hh 93886 2015-11-03 08:28:26Z gcosmo $
//
/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class B1RunAction;

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction();//B1RunAction* runAction);
    virtual ~B1EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    void AddAbs(G4double de);
    void AddGap(G4double de);
  void AddCounter();	
	void AddElCounter();
	void AddInElCounter();
	void AddOtherCounter();
	//    void AddEdep(G4double edep) { fEdep += edep; }
	void SetPosition(G4double position);

  private:
  G4double fEnergyAbs;
  G4double fEnergyGap;
  G4double Counter;
  G4double ElCounter;
  G4double InElCounter;
  G4double OtherCounter; 
  G4double  Position;
  // B1RunAction* fRunAction;
   // G4double     fEdep;
};

inline void B1EventAction::SetPosition(G4double position) {
Position = position;
G4cout << "Position is : " << Position << G4endl;
}

inline void B1EventAction::AddCounter() {
Counter = Counter + 1.0;
//G4cout << "Counts at this point: " << Counter << G4endl;
G4cout << "Counter: " << Counter << G4endl;
}

inline void B1EventAction::AddElCounter() {
ElCounter = ElCounter + 1.0;
G4cout << "ElCounter: " << ElCounter << G4endl;
}

inline void B1EventAction::AddInElCounter() {
InElCounter = InElCounter + 1.0;
G4cout << "InElCounter: " << InElCounter << G4endl;
}

inline void B1EventAction::AddOtherCounter() {
OtherCounter = OtherCounter + 1.0;
G4cout << "OtherCounter: " << OtherCounter << G4endl;
}

inline void B1EventAction::AddAbs(G4double de) {
fEnergyAbs += de;
}

inline void B1EventAction::AddGap(G4double de) {
fEnergyGap += de;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
