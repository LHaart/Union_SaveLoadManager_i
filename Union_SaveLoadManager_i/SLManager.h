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
		// �������� �������
		void Init();
		void loop();

		// ��������� ���� � ����, ��� �������� CanSave()
		// ����������� ����, �� ����� ���� ������ ���� � ������ maxSlot
		void SaveGame( int slot, zSTRING slotName );


		// ������� ��������� ��������
		// ����������� ����, �� ����� ���� ������ ���� � ������ maxSlot
		void LoadGame( int slot );


		bool CanSave();


	private:
		// ������� ���������� �� ini � ������� �������� ����� �����
		int GetCurrentSlotSave();



		// ������� ����������
		// ����... 
		void SaveGameSL();



		// ������� ��������
		// ������ ����� ����� ���������� ���������� - ���������� � ������� ���������
		// � ��������� ���
		void LoadGameSL();
	};
}