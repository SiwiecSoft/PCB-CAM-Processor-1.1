///-----------------------------------------------------------------
///
/// @file      mycurl.h
/// @author    rado4ever
/// Created:   2014-10-30 19:40:34
/// @section   DESCRIPTION
///            MyCurl class declaration
///
///------------------------------------------------------------------

/********************************************************************

Proces instalacji biblioteki CURL dla Dev-C++ wymaga zainstalowania przez nas nastÍpujπcych pakietÛw:
[li]zlib[/li]
[li]openssl[/li]
[li]libcurl[/li]
Aby instalacja przebieg≥a szybko i bezproblemowo warto skorzystaÊ z menu NarzÍdzia -> Sprawdü czy sπ nowe uaktualnienia/pakiety.

W ustawieniach projektu nalezy ustawic:
w konsolidatorze

-l curl
-l winmm 
-l ssl
-l crypto
-l z
-l gdi32
-l ws2_32
        
w kompilator c++
-DCURL_STATICLIB

wiecej na stronie http://cpp0x.pl/forum/temat/?id=83

*********************************************************************/

#ifndef MYCURLLIBRARY
#define MYCURLLIBRARY

#include <stdio.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

#include "wx.h"
#include "rx.h"

class MyCurl;
class PerformThread : public wxThread 
{
	public:
		PerformThread( MyCurl *MyCurlObj, bool *IsDone );
		
	private:
		void* Entry(); // the entry point to the thread
		MyCurl *curlobj;
		bool *isdone;
};

class PerformQueueCtrl
{
    public:
        void Add     ( unsigned int MyCurlID );       // dodaje do kolejki, zglasza chec wykonania performa przez obiekt MyCurl o okteslonym MyCurlID
        void Remove  ( unsigned int MyCurlID );       // usuwa rzadanie z kolejki, powinno byc wykonane po wykonaniu perform przez obiekt
        bool IsMyTurn( unsigned int MyCurlID );       // obiekt pyta czy jest jego kolej podajac swoje MyCurlID
        
    private:
        wxArrayInt priv_Queue;
        
};

class MyCurl
{
    private:
        unsigned int priv_ID;
        PerformQueueCtrl *priv_PerformQueueCtrl;
        
        wxString URL;
        wxString USERPWD;
        wxString COOKIEFILE;
        wxString COOKIEJAR;
        wxString PROXY;
        wxString HEADFILE;
        wxString ANSFILE;
        
        wxArrayString POSTFIELDS;
        wxArrayString HTTPHEADER;
        wxArrayString COOKIES;
        
        bool IGNORECOOKIE;
        bool PostURLEncoding;
        
        wxTextFile MyFile;
        
        PerformThread *PerformThread1;
        bool IsDone;
    
    public:
        MyCurl( unsigned int MyCurlID = 0, PerformQueueCtrl *QueueCtrl = NULL ){ FastInitMyCurl(); priv_ID = MyCurlID; priv_PerformQueueCtrl = QueueCtrl; };
        
        static wxString URLEncode( wxString TextToEncode ) { wxString Ret = curl_escape( TextToEncode.c_str(), TextToEncode.Len() ); return Ret; };
        static wxString URLDecode( wxString TextToDecode ) { wxString Ret = curl_unescape( TextToDecode.c_str(), TextToDecode.Len() ); return Ret; };
        
        static wxString NowGMT()      { time_t now = time(NULL);  return wxString::Format( "%d", mktime( gmtime(&now) ) ); } // ???????????????
        static wxString Now()         { return wxString::Format( "%d", time(NULL) ); }  // ta jest zgodna z java
        static wxString NowJava()     { return Now() + wxString::Format( "%03d", clock() % 1000 ); }
        
        wxString GetFile( wxString FilePath, bool WithEnters = true );
        
        void FastInitMyCurl(int Option = 0) { IGNORECOOKIE = false; IsDone = true; PostURLEncoding = true; ClearAll(); }
        
        void SetUrl(wxString URL)                               { this->URL = URL; }
        void SetUserPWD(wxString USERPWD)                       { this->USERPWD = USERPWD; }
        //void SetInCookieFile(wxString COOKIEFILE = "")          { this->COOKIEFILE = COOKIEFILE; }
        //void SetOutCookieFile(wxString COOKIEJAR = "")          { this->COOKIEJAR = COOKIEJAR; }
        void SetHeaderFile(wxString HEADFILE = "")              { this->HEADFILE = HEADFILE; }
        void SetAnswerFile(wxString ANSFILE = "")               { this->ANSFILE = ANSFILE; }
        void SetIgnoreCookieCommends(bool IGNORECOOKIE = true)  { this->IGNORECOOKIE = IGNORECOOKIE; }
        void SetPostURLEncoding(bool Encoding = true)           { this->PostURLEncoding = Encoding; }
        
        wxString GetUrl()                   { return URL; }
        wxString GetUserPWD()               { return USERPWD; }
        //wxString GetInCookieFile()          { return COOKIEFILE; }
        //wxString GetOutCookieFile()         { return COOKIEJAR; }
        wxString GetHeaderFilePath()        { return HEADFILE; }
        wxString GetAnswerFilePath()        { return ANSFILE; }
        bool GetIgnoreCookieCommends()      { return IGNORECOOKIE; }
        bool GetPostURLEncoding()           { return PostURLEncoding; }
        
        bool MultiFind( wxArrayString *ArrayString, wxString TextToFind, unsigned int *RetInt );      // Przeszukuje tablice wxArrayString i zwraca numer elementu zawierajacego TextToFind do RetInt oraz true w przeciwnym razie zwraca false
        wxArrayString StringToArray( wxString InStr, char Sep );                                      // Pobiera separowany Sep'em tekst InStr i wpisuje skladniki do zwracanego wxArrayString, ignoruje separator na koncu
        wxString      ArrayToString( wxArrayString *InArray, wxString Sep );                          // Tworzy separowany Sep'em tekst z tablicy InArray i zwraca go, nie dodaje separatora na koncu
        
        void ClearAll(){ POSTFIELDS.Clear(); HTTPHEADER.Clear(); COOKIES.Clear(); }
        
        void PostFieldAdd( wxString NameValue ) { POSTFIELDS.Add( NameValue ); }
        void PostFieldAdd( wxString Name, wxString Value ) { POSTFIELDS.Add( Name + "=" + Value ); } 
        void PostFieldAdd( wxArrayString *NameValue ) { for ( unsigned int i = 0; i < NameValue->GetCount(); i++ ) POSTFIELDS.Add( NameValue->Item(i) ); }
        
        void PostFieldSet( wxString Name, wxString Value );                     // Ustawia pole Name formularza na wartosc Value jesli nie ma jeszcze takiego pola to je dodaje
        void PostFieldSet( wxString NameValue );                                // Tozsama z powyzsza z tym ze trzeba uzyc separatora tj. np. "user=qqq"
        void PostFieldSet( wxArrayString *NameValue );                          // Tozsama z powyzsza z tym ze przyjmuje wiele parametrow w postaci wxArrayString
        void PostFieldLoad( wxString MultiLineText, char Sep = '\n' );          // Czysci a nastepnie ustawia wiele pol formularza z wieloliniowego tekstu w formacie jak wyzej, gdzie kolejne wpisy sa w osobnych linijkach ( domyslnie linijki odzielone sa enterami )
        void PostFieldRemove( wxString Name );                                  // Usuwa pole Name formularza, co przesuwa w gore pozostale pola
        void PostFieldRemove( int Number );                                     // Usuwa pole numer Number formularza, co przesuwa w gore pozostale pola
        void PostFieldClear() { POSTFIELDS.Clear(); }                           // Czysci formularz tj. tablice wxArrayString z danymi POST
        wxArrayString PostFieldGetArray() { return POSTFIELDS; }                // Zwraca tablice wxArrayString z danymi POST ( elementy maja format "Name=Value" )
        wxString PostFieldGetString( wxString Sep = "&" );                      // Laczy pojedyncze wpisy z tablicy wxArrayString w jeden ciag za pomoca lacznika '&' i zwraca jako wxString
        
        
        void HttpHeaderSet( wxString Name, wxString Value );                    // Ustawia parametr Name naglowka http na wartosc Value jesli nie ma jeszcze takiego parametru to go dodaje ( Name bez ':' np. Name="Connection", Value="keep-alive" )
        void HttpHeaderSet( wxString NameValue );                               // Tozsama z powyzsza z tym ze trzeba uzyc separatora ": " tj. np. "Connection: keep-alive"
        void HttpHeaderSet( wxArrayString *NameValue );                         // Tozsama z powyzsza z tym ze przyjmuje wiele parametrow w postaci wxArrayString
        void HttpHeaderLoad( wxString MultiLineText, char Sep = '\n' );         // Czysci a nastepnie ustawia wiele parametrow naglowka http z wieloliniowego tekstu w formacie jak wyzej, gdzie kolejne wpisy sa w osobnych linijkach
        void HttpHeaderRemove( wxString Name );                                 // Usuwa parametr Name naglowka http, co przesuwa w gore pozostale pola
        void HttpHeaderRemove( int Number );                                    // Usuwa parametr numer Number naglowka http, co przesuwa w gore pozostale pola
        void HttpHeaderClear() { HTTPHEADER.Clear(); }                          // Czysci naglowek http tj. tablice wxArrayString z jego danymi
        wxArrayString HttpHeaderGetArray() { return HTTPHEADER; }               // Zwraca tablice wxArrayString z danymi naglowka http ( elementy maja format "Name: Value" )
       
       
        void CookieSet( wxString Name, wxString Value );                        // Ustawia ciasteczko Name na wartosc Value jesli nie ma jeszcze takiego ciasteczka to je dodaje
        void CookieSet( wxString NameValue );                                   // Tozsama z powyzsza z tym ze trzeba uzyc separatora tj. np. "cookie=qqq"
        void CookieSet( wxArrayString *NameValue );                             // Tozsama z powyzsza z tym ze przyjmuje wiele parametrow w postaci wxArrayString
        void CookieLoad( wxString MultiLineText, char Sep = '\n' );             // Czysci a nastepnie ustawia wiele parametrow cookie z wieloliniowego tekstu w formacie jak wyzej, gdzie kolejne wpisy sa w osobnych linijkach
        void CookieRemove( wxString Name );                                     // Usuwa ciasteczko Name, co przesuwa w gore pozostale wpisy
        void CookieRemove( int Number );                                        // Usuwa ciasteczko numer Number, co przesuwa w gore pozostale wpisy
        void CookieClear() { COOKIES.Clear(); }                                 // Czysci ciasteczka tj. tablice wxArrayString z nimi
        wxArrayString CookieGetArray() { return COOKIES; }                      // Zwraca tablice wxArrayString z ciasteczkami ( elementy maja format "Name=Value" )
        wxString CookieGetString( wxString Sep = "; " );                        // Laczy pojedyncze wpisy z tablicy wxArrayString w jeden ciag za pomoca lacznika "; " i zwraca jako wxString


        
        void LoadCookiesFromHeadFile(wxString HeadFilePath); // bedzie zawsze nawet z temp HEADFILE pobierac do COOKIES chyba ze IGNORECOOKIE = true
        void LoadCookiesFromCookieFile(wxString InCookieFilePath);
        void WriteCookieToFile(wxString OutCookieFilePath); // uzyc bezmyslnie jesli nie ustawione pole COOKIEFILE funkcja nic nie zrobi
        
        bool IsStringInAnsFile(wxString FindString);
        wxString GetHeaderValue(wxString HeaderName);
        wxString GetLineFromAnsFileContain(wxString FindString);
        
        wxString GetAnswerFile( bool WithEnters = true )    { return GetFile( ANSFILE,  WithEnters ); }
        wxString GetHeaderFile( bool WithEnters = true )    { return GetFile( HEADFILE, WithEnters ); }
        
        void Perform(bool Async = false);
        
        /// obsluga wewnetrznego watku
        
        bool IsRunning() { return !IsDone; };                                   // Zwraca true kiedy watek ptacuje i false kiedy sie zakonczyl
        bool KillThread();                                                      // Zabija watek kiedy jest aktywny i zwraca true lub nic nie robi i zwraca false
};

#endif
