///-----------------------------------------------------------------
///
/// @file      MyConfigFile.cpp
/// @author    rado4ever
/// Created:   2014-10-30 19:40:34
/// @section   DESCRIPTION
///            MyCurl class implementation
///
///------------------------------------------------------------------

#include "inc/mycurl.h"

/*******************************************************************************
**************** Definicja klasy pomocniczej PerformThread *********************
********************************************************************************/

PerformThread::PerformThread( MyCurl *MyCurlObj, bool *IsDone )
{
    curlobj = MyCurlObj;
	isdone  = IsDone;
	*isdone = false;
    
    Create(); // we have to create a thread before we can run it
    Run(); // run our thread
}

void* PerformThread::Entry() 
{
    curlobj->Perform();
	*isdone = true;
	wxMilliSleep(10);
}

/*******************************************************************************
************** Definicja klasy pomocniczej PerformQueueCtrl ********************
********************************************************************************/

void PerformQueueCtrl::Add( unsigned int MyCurlID )          // dodaje do kolejki, zglasza chec wykonania performa przez obiekt MyCurl o okteslonym MyCurlID
{
    priv_Queue.Add( MyCurlID );
}

void PerformQueueCtrl::Remove( unsigned int MyCurlID )       // usuwa rzadanie z kolejki, powinno byc wykonane po wykonaniu perform przez obiekt
{
    priv_Queue.Remove( MyCurlID );
}

bool PerformQueueCtrl::IsMyTurn( unsigned int MyCurlID )     // obiekt pyta czy jest jego kolej podajac swoje MyCurlID
{
    return MyCurlID == priv_Queue.Item(0);
}

/*******************************************************************************
****************** Ogolne funkcje dzialajace na ciagach ************************
********************************************************************************/

bool MyCurl::MultiFind( wxArrayString *ArrayString, wxString TextToFind, unsigned int *RetInt )      // Przeszukuje tablice wxArrayString i zwraca numer elementu zawierajacego TextToFind do RetInt oraz true w przeciwnym razie zwraca false
{
    for ( unsigned int i = 0; i < ArrayString->GetCount(); i++ )     // szukamy czy jest taki wpis w tablicy
    {
        if ( ArrayString->Item(i).Find( TextToFind ) > -1 )          // jak jest to przestajemy szukac i zwracamy numer wiersza gdzie znaleziono
        {
            *RetInt = i;
            return true;
        }
    }
    
    return false;
} 

wxArrayString MyCurl::StringToArray( wxString InStr, char Sep )                                      // Pobiera separowany Sep'em tekst InStr i wpisuje skladniki do zwracanego wxArrayString, ignoruje separator na koncu
{
    wxArrayString RetArray;
    
    while ( !InStr.IsEmpty() )  // wyninanie kolejnych parametrow az do konca
    {
        RetArray.Add( InStr.BeforeFirst( Sep ) ); // dodanie kolejnego elementu do tablicy
        InStr = InStr.AfterFirst( Sep );          // odciecie poczatku
    }
    
    return RetArray;
}

wxString MyCurl::ArrayToString( wxArrayString *InArray, wxString Sep )                               // Tworzy separowany Sep'em tekst z tablicy InArray i zwraca go, nie dodaje separatora na koncu
{
    unsigned int i = 0;
    wxString RetStr = "";
    
    if ( !InArray->IsEmpty() )
    {
        for( i = 0; i < InArray->GetCount() - 1; i++ ) RetStr += InArray->Item(i) + Sep; 
                                                       RetStr += InArray->Item(i);
    }
    
    return RetStr;
}  

/*******************************************************************************
**************************** Funkcje ustawcze **********************************
*******************************************************************************
**************************** Sekcja PostField **********************************
********************************************************************************/

void MyCurl::PostFieldSet( wxString Name, wxString Value )                     // Ustawia pole Name formularza na wartosc Value jesli nie ma jeszcze takiego pola to je dodaje
{
    unsigned int i = 0;
    
    if ( MultiFind( &POSTFIELDS, Name, &i ) ) POSTFIELDS.Item(i) = Name + "=" + Value;
    else                                      POSTFIELDS.Add( Name + "=" + Value );
}

void MyCurl::PostFieldSet( wxString NameValue )                                // Tozsama z powyzsza z tym ze trzeba uzyc separatora tj. np. "user=qqq"
{
    PostFieldSet( NameValue.BeforeFirst('='), NameValue.AfterFirst ('=') ); // wyciagamu Name i Value z argumentu
}

void MyCurl::PostFieldSet( wxArrayString *NameValue )                          // Tozsama z powyzsza z tym ze przyjmuje wiele parametrow w postaci wxArrayString
{
    for ( unsigned int i = 0; i < NameValue->GetCount(); i++ ) PostFieldSet( NameValue->Item(i) );
}

void MyCurl::PostFieldLoad( wxString MultiLineText, char Sep )                 // Czysci a nastepnie ustawia wiele pol formularza z wieloliniowego tekstu w formacie jak wyzej, gdzie kolejne wpisy sa w osobnych linijkach
{
    PostFieldClear();
    PostFieldAdd( &StringToArray( MultiLineText, Sep ) );
}

void MyCurl::PostFieldRemove( wxString Name )                                  // Usuwa pole Name formularza, co przesuwa w gore pozostale pola
{
    
}

void MyCurl::PostFieldRemove( int Number )                                     // Usuwa pole numer Number formularza, co przesuwa w gore pozostale pola
{
    //POSTFIELDS.Remove( Number );
}

wxString MyCurl::PostFieldGetString( wxString Sep )                                          // Laczy pojedyncze wpisy z tablicy wxArrayString w jeden ciag za pomoca lacznika '&' i zwraca jako wxString
{
    if ( PostURLEncoding ) for ( unsigned int i = 0; i < POSTFIELDS.GetCount(); i++ )
    {
        POSTFIELDS.Item(i) = POSTFIELDS.Item(i).BeforeFirst('=') + "=" + URLEncode( POSTFIELDS.Item(i).AfterFirst('=').utf8_str() );
    }

    return ArrayToString( &POSTFIELDS, Sep );
}

/*******************************************************************************
**************************** Sekcja HttpHeader *********************************
********************************************************************************/        
        
void MyCurl::HttpHeaderSet( wxString Name, wxString Value )                    // Ustawia parametr Name naglowka http na wartosc Value jesli nie ma jeszcze takiego parametru to go dodaje ( Name bez ':' np. Name="Connection", Value="keep-alive" )
{
    unsigned int i = 0;
    
    if ( MultiFind( &HTTPHEADER, Name, &i ) ) HTTPHEADER.Item(i) = Name + ": " + Value;
    else                                      HTTPHEADER.Add( Name + ": " + Value );
}

void MyCurl::HttpHeaderSet( wxString NameValue )                               // Tozsama z powyzsza z tym ze trzeba uzyc separatora ": " tj. np. "Connection: keep-alive"
{
    unsigned int i = 0;
    
    if ( MultiFind( &HTTPHEADER, NameValue.BeforeFirst(':'), &i ) ) HTTPHEADER.Item(i) = NameValue;
    else                                                            HTTPHEADER.Add( NameValue );
}

void MyCurl::HttpHeaderSet( wxArrayString *NameValue )                          // Tozsama z powyzsza z tym ze przyjmuje wiele parametrow w postaci wxArrayString
{
    for ( unsigned int i = 0; i < NameValue->GetCount(); i++ ) HttpHeaderSet( NameValue->Item(i) );
}

void MyCurl::HttpHeaderLoad( wxString MultiLineText, char Sep )                // Czysci a nastepnie ustawia wiele parametrow naglowka http z wieloliniowego tekstu w formacie jak wyzej, gdzie kolejne wpisy sa w osobnych linijkach
{
    HttpHeaderClear();
    HttpHeaderSet( &StringToArray( MultiLineText, Sep ) );
}

void MyCurl::HttpHeaderRemove( wxString Name )                                 // Usuwa parametr Name naglowka http, co przesuwa w gore pozostale pola
{
    
}

void MyCurl::HttpHeaderRemove( int Number )                                    // Usuwa parametr numer Number naglowka http, co przesuwa w gore pozostale pola
{
    
}

/*******************************************************************************
**************************** Sekcja Cookie *************************************
********************************************************************************/     
       
void MyCurl::CookieSet( wxString Name, wxString Value )                        // Ustawia ciasteczko Name na wartosc Value jesli nie ma jeszcze takiego ciasteczka to je dodaje
{
    unsigned int i = 0;
    
    if ( MultiFind( &COOKIES, Name, &i ) ) COOKIES.Item(i) = Name + "=" + Value;
    else                                   COOKIES.Add( Name + "=" + Value );
}

void MyCurl::CookieSet( wxString NameValue )                                   // Tozsama z powyzsza z tym ze trzeba uzyc separatora tj. np. "cookie=qqq"
{
    CookieSet( NameValue.BeforeFirst('='), NameValue.AfterFirst ('=') ); // wyciagamu Name i Value z argumentu
}

void MyCurl::CookieSet( wxArrayString *NameValue )                          // Tozsama z powyzsza z tym ze przyjmuje wiele parametrow w postaci wxArrayString
{
    for ( unsigned int i = 0; i < NameValue->GetCount(); i++ ) CookieSet( NameValue->Item(i) );
}

void MyCurl::CookieLoad( wxString MultiLineText, char Sep )                    // Czysci a nastepnie ustawia wiele parametrow cookie z wieloliniowego tekstu w formacie jak wyzej, gdzie kolejne wpisy sa w osobnych linijkach
{
    CookieClear();
    CookieSet( &StringToArray( MultiLineText, Sep ) );
}

void MyCurl::CookieRemove( wxString Name )                                     // Usuwa ciasteczko Name, co przesuwa w gore pozostale wpisy
{
    
}

void MyCurl::CookieRemove( int Number )                                        // Usuwa ciasteczko numer Number, co przesuwa w gore pozostale wpisy
{
    
}

wxString MyCurl::CookieGetString( wxString Sep )                                             // Laczy pojedyncze wpisy z tablicy wxArrayString w jeden ciag za pomoca lacznika "; " i zwraca jako wxString
{
    return ArrayToString( &COOKIES, Sep );
}

/*******************************************************************************/
/*******************************************************************************/
/************************ Funkcje do zmiany ************************************/
/*******************************************************************************/
/*******************************************************************************/



static size_t write_data_toFile(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

void MyCurl::LoadCookiesFromHeadFile(wxString HeadFilePath)
{
    wxTextFile HeadFile(HeadFilePath);
    
    if ( HeadFile.Exists() ) HeadFile.Open(HeadFilePath);
    
    for ( unsigned int i = 0; i < HeadFile.GetLineCount(); i++ )
    {
        wxString Cookie = "";
        int j = 0;
        
        int FirstChar = HeadFile.GetLine(i).Lower().Find("< set-cookie: ") + 14;
        
        if ( FirstChar >= 14 )
        {
            int LastChar = HeadFile.GetLine(i).Find(';');
            
            if ( LastChar > 0 ) Cookie = HeadFile.GetLine(i).Mid(FirstChar, LastChar - FirstChar);
            else                Cookie = HeadFile.GetLine(i).Remove(0,14);
            
            //CookieSet( ElementOfString(1, Cookie, '='),  ElementOfString(2, Cookie, '=') );
            CookieSet( Cookie );
        }
    }
    
    if ( HeadFile.IsOpened() ) HeadFile.Close();
}

void MyCurl::LoadCookiesFromCookieFile(wxString InCookieFilePath)
{
    
}

void MyCurl::WriteCookieToFile(wxString OutCookieFilePath)
{
    
}

bool MyCurl::IsStringInAnsFile(wxString FindString)
{
    wxTextFile AnsFile(ANSFILE);
    
    if ( AnsFile.Exists() ) 
    {
        AnsFile.Open(ANSFILE);
        
        for ( unsigned int i = 0; i < AnsFile.GetLineCount(); i++ )
        {
            if ( AnsFile.GetLine(i).Find(FindString) >= 0 )
            {
                AnsFile.Close();
                return true;
            }
        }
    }
    
    if ( AnsFile.IsOpened() ) AnsFile.Close();
    
    return false;
}

wxString MyCurl::GetHeaderValue(wxString HeaderName)
{
    wxTextFile HeadFile(HEADFILE);
    int FindPos;
    wxString Str;
    
    if ( HeadFile.Exists() ) 
    {
        HeadFile.Open(HEADFILE);
        
        for ( unsigned int i = 0; i < HeadFile.GetLineCount(); i++ )
        {
            Str = HeadFile.GetLine(i);
            FindPos = Str.Find(HeaderName);
            if ( FindPos >= 0 )
            {
                HeadFile.Close();
                return Str.Right( Str.Len() - 1 - FindPos - HeaderName.Len() );
            }
        }
    }
    
    if ( HeadFile.IsOpened() ) HeadFile.Close();
    
    return "";
}

wxString MyCurl::GetLineFromAnsFileContain(wxString FindString)
{
    wxTextFile AnsFile(ANSFILE);
    int FindPos;
    wxString Str;
    
    if ( AnsFile.Exists() ) 
    {
        AnsFile.Open(ANSFILE);
        
        for ( unsigned int i = 0; i < AnsFile.GetLineCount(); i++ )
        {
            Str = AnsFile.GetLine(i);
            FindPos = Str.Find(FindString);
            if ( FindPos >= 0 )
            {
                AnsFile.Close();
                return Str;//.Right( Str.Len() - 1 - FindPos - FindString.Len() );
            }
        }
    }
    
    if ( AnsFile.IsOpened() ) AnsFile.Close();
    
    return "";
}

wxString MyCurl::GetFile( wxString FilePath, bool WithEnters )
{
    wxTextFile File(FilePath);
    wxString Val = "";
    
    if ( File.Exists() ) 
    {
        File.Open(FilePath);
        
        for ( unsigned int i = 0; i < File.GetLineCount(); i++ ) 
        { 
            Val += File.GetLine(i); 
            if( WithEnters ) Val += "\n"; // to znaczy jeden znak 10
        }
    }
    
    if ( File.IsOpened() ) File.Close();
    
    return Val; 
}

void MyCurl::Perform(bool Async)
{
    if ( Async )
    {
        PerformThread1 = new PerformThread( this, &IsDone );
    }
    else
    {  
        CURL *curl;
        CURLcode res;
        struct curl_slist *slist=NULL;
        
        FILE *pagefile;
        FILE *headfile;
    
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        
        wxString postfields = PostFieldGetString();
        wxString cookies = "Cookie: " + CookieGetString();
        
        if(curl)
        {
            // zarejestrowanie performa
            if ( priv_PerformQueueCtrl != NULL ) priv_PerformQueueCtrl->Add( priv_ID );
            
            curl_easy_setopt(curl, CURLOPT_URL, URL.c_str() ); // obie tak samo dzia³¹j¹
            
            curl_easy_setopt(curl, CURLOPT_ENCODING, ""); // automatyczne rozkodowanie
            
            if ( !POSTFIELDS.IsEmpty() ) curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str() );
     
            if ( !HTTPHEADER.IsEmpty() ) 
            {
                for( unsigned int i = 0; i < HTTPHEADER.GetCount(); i++ )  
                {
                    slist = curl_slist_append(slist, HTTPHEADER.Item(i).c_str() );
                }
            }   
            
            slist = curl_slist_append(slist, cookies.c_str() );
            
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
            
            // ominiecie CA
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            
            //curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "");
            
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            
            if ( HEADFILE.IsEmpty() )  headfile = fopen("temphead", "wb"); 
            else                       headfile = fopen(HEADFILE, "wb"); 
            
            pagefile = fopen(ANSFILE, "wb"); // open the file 
            
            if ( headfile ) 
            {
                curl_easy_setopt(curl, CURLOPT_STDERR, headfile );
                
                if ( pagefile )
                {
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_toFile);
                    curl_easy_setopt(curl, CURLOPT_FILE, pagefile); // write the page body to this file handle. CURLOPT_FILE is also known as
                }
                
                if ( priv_PerformQueueCtrl != NULL ) while ( !priv_PerformQueueCtrl->IsMyTurn( priv_ID ) ) { wxMilliSleep(10); } // czekanie na swoja kolej
                
                // Perform the request, res will get the return code 
                res = curl_easy_perform(curl);
            }
            
            fclose(headfile);
            fclose(pagefile);
            
            // Check for errors
            if(res != CURLE_OK)    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    
            // always cleanup 
            curl_easy_cleanup(curl);
            
            // wyrejestrowanie performa
            if ( priv_PerformQueueCtrl != NULL ) priv_PerformQueueCtrl->Remove( priv_ID );
        }
        
        curl_global_cleanup(); 
        
        if ( !IGNORECOOKIE )
        {
            if( HEADFILE.IsEmpty() ) LoadCookiesFromHeadFile("temphead");
            else                     LoadCookiesFromHeadFile(HEADFILE);
        }
        
        if ( HEADFILE.IsEmpty() && wxFileExists("temphead") )  wxRemoveFile("temphead"); 
    }
}

bool MyCurl::KillThread()
{
    if ( IsDone )   return false;
    else            
    {
        PerformThread1->Kill();
        IsDone = true;
        return true;
    }
}


