// ARZUM AYDIN 23.11.2021

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

int compare_str(string a, string b)
{
    int i = 0;
    while(a[i] && b[i]) // iterate through a and b, if there is uppercase letters, make them lowercase
    {
        a[i] = tolower(a[i]);
        b[i] = tolower(b[i]);
        i++;
    }

    // compare all lowercase strings because sorting is case insensitive
    if(a.compare(b) < 0) // if a is lexicographically smaller than b, return 1
    {
        return 1;
    }
    else if(a.compare(b) == 0) // if equal, return 0
    {
        return 0;
    }
    return -1; // if bigger, return -1
}

void swap(vector<string>* a, vector<string>* b) //swap handling function
{
    (*a).swap(*b); // swap function from vector class   
}

int partition(vector<vector<string>>& data, int low, int high, string s)
{
    if(s == "randomized")
    {
        int index = rand() % (high - low) + low; // choose a random index between low and high
        swap(data[high], data[index]);   // take pivot to end of array by swapping with last element 
    }
    // if it is deterministic, choose pivot as the last element

    int i = low - 1; // i holds the place where pivot should be
    for(int j = low; j < high; j++) // iterate through array until pivot is reached
    {
        if( compare_str(data[j][5], data[high][5]) == 1) // compare country names if data[j][5] < data[high][5]
        {
            i++; //increment i to next position
            swap(&data[i], &data[j]); // swap left and right elements with respect to pivot
        }
        else if( compare_str(data[j][5], data[high][5]) == 0) // if countries are same
        {
            if( compare_str(data[j][3], data[high][3]) == 1) // compare artist names
            {
                i++; //increment i to next position
                swap(&data[i], &data[j]); // swap left and right elements with respect to pivot
            }
            else if( compare_str(data[j][3], data[high][3]) == 0) // if artist are same
            {
                if( compare_str(data[j][2], data[high][2]) == 1) // compare unixtime
                {
                    i++; //increment i to next position
                    swap(&data[i], &data[j]); // swap left and right elements with respect to pivot
                }
            }
        }
    }

    i++;
    swap(data[i], data[high]); // assign pivot to its correct place
    return i; // return pivot index
}

void quickSort(vector<vector<string>>& data, int low, int high, string s)
{
    if(low < high)
    {
        // do partition by dividing elements into two groups as smaller than pivot and bigger than pivot
        int pivot_index = partition(data, low, high, s);  // find pivot index by partitioning the array
        quickSort(data, low, pivot_index - 1, s); // quicksort subarray on the left of pivot
        quickSort(data, pivot_index + 1, high, s); // quicksort subarray on the right of pivot
    }
}

int main(int argc, char *argv[])
{
    clock_t t; // clock the algorithm
    int tweets_number = 0; // number of tweets to be sorted
    string algorithm_name = ""; // deterministic or randomized quicksort
    ifstream fin; // input csv filename
    fin.open(argv[3]);
    ofstream fout; // output csv file name
    string line, word;
    vector<vector<string>> data;
    vector<string> row;

    tweets_number = strtol(argv[1], nullptr, 0); // number of tweets is taken from command line argument 1 (N)
    int count_lines = 0; 
    
    if (!fin.is_open()) // error handling
    {
      cerr<<"Could not open file\n";
      exit(1);
    }
    else {
        while(fin && count_lines <= tweets_number) // while not end of file and count < N, read tweets
        {
            getline(fin, line); // get the next line from file
            row.clear();
            stringstream mystr(line); // break line into words via stringstream
            
            if(count_lines != 0) // do not include first row of headers
            {
                while(getline(mystr, word, '\t')) // get words that are seperated with a delimeter
                {
                    row.push_back(word); // push word into vector row
                }
                data.push_back(row); // push vector row into vector data
            } 
            
            count_lines++;
        }
    }

    fin.close();

    
    int low = 0;
    int high = tweets_number - 1;
    
    t = clock();
    quickSort(data, low, high, argv[2]); 
    t = clock() - t;

    fout.open(argv[4]);
    fout << "tweet_id\t" << "tweet_datetime\t" << "tweet_unixtime\t"<< "artist_name\t" <<"track_title\t" << "country\n";
    for(int i = 0; i < tweets_number; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            fout << data[i][j]; // write elements into output csv
            if(j != 5)
            {
                fout << '\t'; // tab seperated 
            }
        }
        fout << '\n';
    }
    fout.close();

    if(strcmp(argv[2],"deterministic") == 0)
    {
        cout << "Sorted in "<<  ((float)t)/CLOCKS_PER_SEC * 1000.0 <<" miliseconds by using deterministic pivot selection."<< endl;
    }
    else
    {
        cout << "Sorted in "<< ((float)t)/CLOCKS_PER_SEC * 1000.0 << " miliseconds by using randomized pivot selection." << endl;
    }
    
    return 0;
}