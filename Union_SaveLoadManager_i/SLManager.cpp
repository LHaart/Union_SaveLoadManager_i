// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {

	void SLManager::Init() {
		
		nameQSaveGame = zoptions->ReadString( "SLManager", "nameQSaveGame", "QuickSave" );
		zSTRING sKeySave = zoptions->ReadString( "SLManager", "keySave", "F10" );
		zSTRING sKeyLoad = zoptions->ReadString( "SLManager", "keyLoad", "F12" );
		keySave = zinput->GetControlValueByName( sKeySave );
		keyLoad = zinput->GetControlValueByName( sKeyLoad );
		youDie = zoptions->ReadString( "SLManager", "youDie", "Вы мертвы!" );
		cantBeSaved = zoptions->ReadString( "SLManager", "cantBeSaved", "Нельзя сохраниться!" );
		slotStr = zoptions->ReadString( "SLManager", "slotString", "Игра сохранена. Слот:" );

#if ENGINE < Engine_G2
		maxSlot = 15;
#else
		maxSlot = 20;
#endif // ENGINE != Engine_G1A
	}

	// Add your code here . . .
	void SLManager::loop() {
		if ( !isPause && player ) {
			// save
			if ( zKeyToggled( keySave ) ) {
				if ( player->attribute[NPC_ATR_HITPOINTS] > 0 ) {

					if ( CanSave() ) {
						SaveGameSL();
					} else {
						printWin( cantBeSaved );
					}

				} else {
					printWin( youDie );
				}
			} 
			// load
			else if ( zKeyToggled( keyLoad ) && oCInformationManager::GetInformationManager().HasFinished() ) {
				LoadGameSL();
			}
		}
	}


	void SLManager::SaveGame( int slot, zSTRING slotName ) {
		if ( slot < 0 || slot > maxSlot )
			return;

		gameMan->savegameManager->GetSavegame( slot )->SetName( slotName );

		ogame->WriteSavegame( slot, 1 );

		printWin( slotStr + " " + ToStr slot );
		gameMan->savegameManager->Reinit();
	}


	void SLManager::LoadGame( int slot ) {
		if ( slot < 0 || slot > maxSlot - 1 )
			return;
		ogame->LoadSavegame( slot, slot );
	}


	bool SLManager::CanSave() {
		return (
			player
			&& player->fmode == NPC_WEAPON_NONE
			&& oCInformationManager::GetInformationManager().HasFinished()
			&& player->anictrl->state == zCAIPlayer::zMV_STATE_STAND
			&& !player->inventory2.IsOpen()
			&& !ogame->game_testmode
			&& player->GetAnictrl()->walkmode != BS_SWIM
			&& player->attribute[ NPC_ATR_HITPOINTS ]
			&& ogame->GetHeroStatus() == oHERO_STATUS_STD
			);
	}



	int SLManager::GetCurrentSlotSave() {
		int minSlotToSave = zoptions->ReadInt( "SLManager", "minSlotSL", 10 );
		int maxSlotToSave = zoptions->ReadInt( "SLManager", "maxSlotSL", 15 );
		int lastSlot = zoptions->ReadInt( "SLManager", "lastSaveSlotSL", 9 );

		if ( lastSlot < minSlotToSave || lastSlot >= maxSlotToSave )
			lastSlot = minSlotToSave - 1;

		if ( lastSlot < 0 )
			lastSlot = 0;
		else if ( lastSlot > maxSlot )
			lastSlot = maxSlot - 1;

		return ++lastSlot;
	}




	void SLManager::SaveGameSL() {
		int currSlot = GetCurrentSlotSave();
		int numberSave = zoptions->ReadInt( "SLManager", "numberSaveSL", 0 );

		gameMan->savegameManager->GetSavegame( currSlot )->SetName( nameQSaveGame + ToStr numberSave );

		ogame->WriteSavegame( currSlot, 1 );

		printWin( slotStr + " " + ToStr currSlot );

		gameMan->savegameManager->Reinit();

		zoptions->WriteInt( "SLManager", ( ToStr "lastSaveSlotSL" ).ToChar(), currSlot, 0 );
		zoptions->WriteInt( "SLManager", ( ToStr "numberSaveSL" ).ToChar(), ++numberSave, 0 );
		zoptions->Save( "Gothic.ini" );
	}



	void SLManager::LoadGameSL() {
		int lastSlot = zoptions->ReadInt( "SLManager", "lastSaveSlotSL", 9 );

		ogame->LoadSavegame( lastSlot, lastSlot );
	}
}