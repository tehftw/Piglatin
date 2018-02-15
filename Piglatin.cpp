
/**
    Pig latin

    Pig Latin – Pig Latin is a game of alterations played on the English language game.
To create the Pig Latin form of an English word the initial consonant sound is transposed to the end of the word and an ay is affixed
(Ex.: "banana" would yield anana-bay).
//*/


/**
TODO: add a general character checking procedure that outputs an "int" type code(from enum)
TODO: add checking if the input is valid for the algorithm
TODO: fix it so that it grabs the first sound, instead of first letter
TODO: add read/write into textfile
//*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace tehpiglatin
{
    void basicPiglatinConsoleMenu();


    bool characterIsConsonant(const char);
    bool characterIsDelimiter(const char);
    bool characterIsAllowed(const char);


    string getSanitizedInput(const string);

    vector<string> splitStringIntoWords(const string);
    string mergeWordsVectorIntoString(const vector<string>, const char);

    void displayVectorOfWords(const vector<string>, char);

    string getPigLatinOfWord(const string); /// Relies on it being a word, all lowercase(no spaces)
    vector<string> getPigLatinOfWordsVector(const vector<string>);


    string getPigLatinOfInputString(const string);


    bool PRINT_LOT_OF_DEBUG_STUFF = false;
}
using namespace tehpiglatin;




/// main()
int main()
{
    basicPiglatinConsoleMenu();
}




/// definitions
void tehpiglatin::basicPiglatinConsoleMenu()
{
    string input;

    cout << "\nPig Latin :D";

    cout << "\nPig Latin – Pig Latin is a game of alterations played on the English language game.";
    cout << "\nCurrently this program works by moving the first consonant to the end and adding suffix '-ay'.";
    cout << "\nEx.: 'banana' would yield 'ananabay'.";

    cout << "\n Write some words(only lowercase and spaces are legal! if you input anything bad I'll tell Santa Claus): ";
    getline(cin, input);

    if(PRINT_LOT_OF_DEBUG_STUFF)
    {
        cout << "(input length = " << input.size() << ")";
    }

    const string piglatinized = getPigLatinOfInputString(input);
    cout << "\n Your words piglatinized: " << piglatinized;
}



/// Function Definitions
bool tehpiglatin::characterIsConsonant(const char checked_character)
{
    // decls
    static const string string_consonants = "qwrtpsdfghjklzxcvbnmQWRTPSDFGHJKLZXCVBNM";

    // code
    for(const char consonant : string_consonants)
    {
        if(checked_character == consonant)
        {
            return true;
        }
    }
    return false;
}


bool tehpiglatin::characterIsDelimiter(const char checked_character)
{
    // decls
    static const string string_of_delimiters  = " \0\n";

    // code
    for(const char delimiter : string_of_delimiters)
    {
        if(checked_character == delimiter)
        {
            return true;
        }
    }
    return false;
}


bool tehpiglatin::characterIsAllowed(const char checked_character)
{
    // decls
    static const string string_of_allowed_input_characters = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ";

    // code
    for(const char character : string_of_allowed_input_characters)
    {
        if(checked_character == character)
        {
            return true;
        }
    }
    return false;
}


string tehpiglatin::getSanitizedInput(const string input_string)
{
    string sanitized_string;
    sanitized_string.reserve(input_string.size() );
    if(PRINT_LOT_OF_DEBUG_STUFF)
    {
        cout << "\n";
        cout << "(sizeof input = " << input_string.size() << ")";
        cout << "(sizeof of sanitized = " << sanitized_string.size() << ")";
    }
    // Iterate through the whole string,
    // while building another string that only consists of legal characters(any illegals are discarded)

    for(char cur_character : input_string)
    {
        if( characterIsAllowed(cur_character ) )
        {
            sanitized_string.push_back(cur_character);
        }
    }

    return sanitized_string;
}


vector<string> tehpiglatin::splitStringIntoWords(const string input_string)
{
    //      decls
    vector<string> vector_of_words;
    string current_word;


    //      code
    if(PRINT_LOT_OF_DEBUG_STUFF)
    {
        cout << "\n TERRIBLE DEBUG OF STRINGSPLITTER XD";
    }

    for( char current_character : input_string )
    {
        if(PRINT_LOT_OF_DEBUG_STUFF)
        {
            cout << "\n ";
        }

        if( characterIsDelimiter(current_character)  )
        {
            if(PRINT_LOT_OF_DEBUG_STUFF)
            {
                cout << "Character '" << current_character << "' is a delimiter. Adding '" << current_word << "' to the vector.";
            }
            // add the current word to vector and clear the operating string
            vector_of_words.push_back(current_word);
            current_word.clear();
        }
        else
        {
            if(PRINT_LOT_OF_DEBUG_STUFF)
            {
                cout << "Adding '" << current_character << "' to the string.";
            }
            current_word += current_character;
            if(PRINT_LOT_OF_DEBUG_STUFF)
            {
                cout << " (string is: " << current_word << ")";
            }
        }
    }

    if(PRINT_LOT_OF_DEBUG_STUFF)
    {
        cout << "\nAdding the last word to vector.";
    }
    vector_of_words.push_back(current_word);



    vector_of_words.shrink_to_fit();
    return vector_of_words;
}


void tehpiglatin::displayVectorOfWords(const vector<string> vector_of_words, char delimiter)
{
    for(string current_word : vector_of_words)
    {
        cout << delimiter << current_word;
    }
}


string tehpiglatin::getPigLatinOfWord(const string input_word)
{

    // decls
    static const string piglatin_suffix = "ay";
    const char first_character = input_word[0];

    // code
    if( characterIsConsonant(first_character) )
    {
        // size_t input_length = input_word.size();
        string piglatinized_word = input_word;


        // 1. Push the first consonant to the end
        // 1.1. Get substring(1, last) - remove the first consonant
        piglatinized_word = input_word.substr( 1,  (input_word.size() - 1) );
        // 1.1. Move all the characters(from 1 to size-1) back by one
        /*
        for(size_t i = 1; i<input_length; i++ )
        {
            piglatinized_string.at(i-1) = piglatinized_string.at(i);
        } // */

        // 1.2. Set the last character to what used to be first
        piglatinized_word += first_character;


        // 2. Add the suffix
        piglatinized_word += piglatin_suffix;


        return piglatinized_word;
    }
    else
    {
        return input_word;
    }
}


vector<string> tehpiglatin::getPigLatinOfWordsVector(const vector<string> vector_of_words_input)
{
    vector<string> vector_of_words_piglatinized;
    vector_of_words_piglatinized.reserve( vector_of_words_input.size() );

    if(PRINT_LOT_OF_DEBUG_STUFF)
    {
        cout << "\n piglatinizing the wordsvector.";
        cout << "(sizeof input = " << vector_of_words_input.size() << ")";
        cout << "(sizeof piglatinized = " << vector_of_words_piglatinized.size() << ")";
    }


    for( string current_word : vector_of_words_input )
    {
        vector_of_words_piglatinized.push_back( getPigLatinOfWord(current_word) );
    }

    return vector_of_words_piglatinized;
}


string tehpiglatin::mergeWordsVectorIntoString(const vector<string> vector_of_words, const char delimiter)
{
    string merged_string;
    for( const string current_part : vector_of_words )
    {
        merged_string += current_part;
        merged_string += delimiter;
    }
    merged_string.pop_back(); // last delimiter isn't needed
    return merged_string;
}


string tehpiglatin::getPigLatinOfInputString(const string input_string)
{
    const string sanitized_input_string = getSanitizedInput(input_string);
    if(PRINT_LOT_OF_DEBUG_STUFF)
    {
        cout << "\n Sanitized input: "  << sanitized_input_string  ;
    }
    const vector<string> vector_of_words = splitStringIntoWords(sanitized_input_string );
    const vector<string> vector_of_words_piglatinized = getPigLatinOfWordsVector(vector_of_words);

    return  mergeWordsVectorIntoString(vector_of_words_piglatinized, ' ');
}






