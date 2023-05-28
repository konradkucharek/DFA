#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//------------------------------------------------
// DFA->Scanner Function
// Name: Konrad Kucharek
//------------------------------------------------

// ---------- DFAs follow -------------------------

// This FA is for a b^+
bool mytoken(string s)
{ 
  int state = 0;
  int charpos = 0;

  cout << "Trying the mytoken machine..." << endl;  
 
  while (s[charpos] != '\0') 
    {
      cout << "current state: " << state << endl;
      cout << "character: " << s[charpos] << endl;
 
      if (state == 0 && s[charpos] == 'a') // If the current state is 0 and char is an 'a', new state is 1
      state = 1;
      else if (state == 1 && s[charpos] == 'b') // If the current state is 1 and char is a 'b', new state is 2
      state = 2;
      else if (state == 2 && s[charpos] == 'b') // If the current state is 2 and char is a 'b', stay in state 2
      state = 2;
      else
	{
	  cout << "I am stuck in state " << state << endl; // Otherwise, string fails DFA
	  return(false);
	}
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
}// end of mytoken


// IDENT DFA 
bool ident_token(string s)
{
  	int state = 0;
	int charpos = 0;

	cout << "Trying ident_token machine..." << endl;

	while(s[charpos] != '\0')
	{
		cout << "current state: " << state << endl;
		cout << "character: " << s[charpos] << endl;

		if(state == 0 && s[charpos] == 'a') 
		{
			state = 1;
		}
		else if(state == 0 && s[charpos] == 'b')
		{
			state = 1;
		}
		else if(state == 1 && s[charpos] == 'a')
                {
                        state = 1;
                }
                else
                if(state == 1 && s[charpos] == 'b')
                {
                        state = 1;
                }
		else if(state == 1 && s[charpos] == '2')
                {
                        state = 1;
                }
        else if(state == 1 && s[charpos] == '3')
                {
                        state = 1;
                }
		else if(state == 1 && s[charpos] == '_')
		{
			state = 1;
		}
		else
		{
			cout << "I am stuck in state " << state << endl;
			return(false);
		}
		charpos++;
	}
	if (state == 1)
	{
		return(true);
	}
	else return(false);
}


// REAL DFA 
bool real_token(string s)
{
	int state = 0;
	int charpos = 0;

	cout << "Trying real_token machine..." << endl;
	
	while(s[charpos] != '\0')
	{
		cout << "current state: " << state << endl;
                cout << "character: " << s[charpos] << endl;

		if(state == 0 && s[charpos] == '2')
		{
			state = 0;
		}
		else
		if(state == 0 && s[charpos] == '3')
		{
			state = 0;
		}
		else
		if(state == 0 && s[charpos] == '.')
                {
                        state = 1;
                }
		else
		if(state == 1 && s[charpos] == '2')
                {
                        state = 2;
                }
		else
		if(state == 1 && s[charpos] == '3')
                {
                        state = 2;
                }
		else
		if(state == 2 && s[charpos] == '2')
                {
                        state = 2;
                }
		else
		if(state == 2 && s[charpos] == '3')
                {
                        state = 2;
                }
		else
		{
			cout << "I am stuck in state " << state << endl;
			return(false);
		}
		charpos++;
	}
	if(state == 2)
	{
		return(true);
	}
	else return(false);
}


// INT DFA 
bool integer_token(string s)
{
  	int state = 0;
	int charpos = 0;

	cout << "Trying integer_token machine..." << endl;

	while(s[charpos] != '\0')
	{
	
	cout << "current state: " << state << endl;
	cout << "character: " << s[charpos] << endl;

	if(state == 0 && s[charpos] == '2')
	{
		state = 1;
	}
	else
	if(state == 0 && s[charpos] == '3')
	{
		state = 1;
	}
	else
	if(state == 1 && s[charpos] == '2')
	{
		state = 1;
	}
	else
	if (state == 1 && s[charpos] == '3')
	{
		state = 1;
	}
	else
	{
		cout << "I am stuck in state" << state << endl;
		return(false);
	}
	charpos++;
	}
	if(state == 1)
	{
		return(true);
	}
	else return(false);
}

// -----------------------------------------------------

enum tokentype {ERROR, MYTOKEN, IDENT, REAL, INT};
int scanner(tokentype& , string& );  // to be called by main
fstream fin;   // file stream to use

// The test-driver -- NO NEED TO CHANGE THIS
int main()
{ string fname;
  cout << "Enter the input file name:";
  cin >> fname; 

  fin.open( fname.c_str(), fstream::in);

  string tokens[5] = {"ERROR", "MYTOKEN", "IDENT", "REAL", "INT"};
  tokentype thetype;
  string theword; 

  while (true)  // keep going 
    {
      scanner(thetype, theword);  // the paramers will be set by Scanner
      if (theword == "EOF") break;

      cout << ">>>>>Type is:" << tokens[thetype]  << endl;
    }

  cout << ">>>>>End of File encountered" << endl;  
  fin.close();
} 


// Scanner sets the_type and w
int scanner(tokentype& the_type, string& w)
{
  
  // This goes through all machines one by one on the input string w

	cout << endl;
	cout << ".....Scanner was called..." << endl;

	fin >> w;  // grab next word from fain.txt
	cout << ">>>>>Word is:" << w << endl;   

	if(mytoken(w))
	{ 
		the_type = MYTOKEN; 
	}
  
  // Other if-then's added here in the right order to go through
  // all FAs one by one and set the_type to be IDENT, REAL or INT.
	if(ident_token(w))
	{
		the_type = IDENT;
	}

	else if(real_token(w))
	{
		the_type = REAL;
	}

	else if(integer_token(w))
        {
                the_type = INT;
        }

	else // none of the FAs returned TRUE
	{ 
	cout << ">>>>> Lexical Error: The string is not in my language" << endl;
      	the_type = ERROR; 
	}

}