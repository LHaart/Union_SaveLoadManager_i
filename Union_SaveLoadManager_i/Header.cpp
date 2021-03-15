// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Add your code here . . .
#define isPause ogame->singleStep
#define ToStr (zSTRING)
#define printWin(a) ogame->game_text->Printwin(ToStr a);

	void oCSavegameInfo::SetName( zSTRING name ) {
		m_Name.Clear();
		m_Name.Put(  zSTRING( name ), m_Name.Length() );
	}
}