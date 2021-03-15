// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {
	// Add your code here . . .

	class SLManager {
	public:
		zSTRING nameQSaveGame;
		zSTRING youDie;
		zSTRING cantBeSaved;
		zSTRING slotStr;
		int keySave;
		int keyLoad;
		int maxSlot;
	public:
		// основная функция
		void Init();
		void loop();

		// сохраняет игру в слот, без проверки CanSave()
		// проверяется слот, не может быть меньше нуля и больше maxSlot
		void SaveGame( int slot, zSTRING slotName );


		// функция свободной загрузки
		// проверяется слот, не может быть меньше нуля и больше maxSlot
		void LoadGame( int slot );


		bool CanSave();


	private:
		// считать переменные из ini и вернуть валидный номер слота
		int GetCurrentSlotSave();



		// функция сохранения
		// счит... 
		void SaveGameSL();



		// функция загрузки
		// читает номер слота последнего сохранения - сделанного с помощью менеджера
		// и загружает его
		void LoadGameSL();
	};
}