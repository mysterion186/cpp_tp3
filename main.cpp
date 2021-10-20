#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
#include <list>
#include <deque> 
#include <sstream> 

using namespace std;

// fonction pour intervertir la valeur entre 2 itérateurs
template <typename  T>
void sorted_container(T & v){
    for (auto it_1 = v.begin();it_1!=v.end();++it_1){
        for (auto it_2 = it_1;it_2!=v.end();++it_2){
            // pb lorsqu'on fait un swap les itérateurs font n'importe quoi
            if (*it_1 > *it_2){ // condition de tri pour l'instant on garde ça mais faudra sûrement le changer plus tard
                iter_swap(it_1,it_2);
            }
        }
    }    
}

// fonction pour afficher les éléments des conteneurs 
template <typename T>
void display(T& v){
    cout << "appel de la fonction test_afficher"<<endl;
    for (auto it_1 = v.begin();it_1<v.end();++it_1){
        cout<<"affichage des valeurs avec it1 "<<*it_1<<endl;
    }    
}

// fonction pour écrire dans le fichier texte à partir du conteneur 
// t est un conteneur trié
template<typename T>
void write_contenue(T t,const string& file_name){
    string type,conteneur,line; 
    ifstream my_file_read(file_name);
    int line_num = 0;
    if(my_file_read.is_open()){
        while(getline(my_file_read, line))
        {
            if (line_num==0){
                type=line;  
            }
            else if (line_num==1){
                conteneur = line;
            }
            else {
                break; // on quitte le fichier une fois qu'on a les 2 premières lignes 
            }
            line_num++;
        }
        my_file_read.close();
    }
    else{
        cout<<"impossible de lire le fichier"<<endl;
    }

    ofstream my_file("result.txt");
    if (my_file.is_open()){
        // ajout du type + conteneur 
        my_file<<type<<"\n"<<conteneur<<endl;
        // boucle for pour itérer sur les valeurs triées
        for(auto it_1 = t.begin();it_1!=t.end();++it_1) {
            my_file<<*it_1<<"\n";
        }
        my_file.close();
    }
    else {
        cout<<"impossible d'ouvrir le fichier"<<endl;
    }
}

// fonction pour lire le fichier et mettre les lignes dans un conteneur 
vector<string> read_file(const string& filename){
    vector<string> vect;
    string line; 
    ifstream my_file(filename);
    // partie lecture du fichier
    if (my_file.is_open()) 
    {
        while(getline(my_file, line)){
            vect.push_back(line);
        }
        my_file.close();
    }
    else {
        cout<<"impossible d'ouvrir le fichier"<<endl;
    } 
    return vect; 
}

// fonction pour écrire ce qu'on a dans les conteneurs spécifique 
template<class T>
void write_buffer(vector<string> & src,  T & dst){ // src contient le vecteur avec les lignes, dst sera le conteneur choisi dans le fichier 
    typename T::value_type get_type_value;
    //cout<<typeid(get_type_value).name()<<endl;
    for (auto it_1 = src.begin()+2;it_1<src.end();++it_1){ // on commence à 2 pour ne pas afficher les type des variables + conteneurs 
        decltype(get_type_value) temp; // variable temporaire qui va nous servir pour la conversion 
        stringstream convert_ss; // stringstream qui va nous aider à faire une conversion "direct" 
        convert_ss<<*it_1; 
        convert_ss>>temp;  // conversion de string vers le type du conteneur 
        dst.push_back(temp);  // ajout de l'élément dans le conteneur 
    }
}

// fonction pour lire/écrire dans le buffer/convertir/écrire dans le fichier 
template<typename T> 
void write(vector<string> & vect,const string & filename,T t){
    write_buffer(vect,t); // on recopie les valeurs de vect dans le conteneur avec le bon type 
    sorted_container(t); // on trie le conteneneur 
    write_contenue(t,filename); // on

}

int main(int argc, char** argv){
    vector<string> vect = read_file(argv[1]); // il faut mettre le nom du fichier en même temps que l'exécution du prgm 
    // partie pour déterminer le type de conteneur à utiliser selon le fichier text 
    cout<< "On va travailler avec : \ntype des variables "<<vect[0]<<"\ntype de conteneur "<<vect[1]<<endl;
    
    
    // cout<<"test_2 : "<<test_2<<endl;
    // cas entier 
    if (vect[0][0]=='i'){
        if (vect[1][0]=='v'){
            cout<< "on travaille avec vector int "<<endl;
            vector<int> temp;
            write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='d'){
            cout<< "on travaille avec deque int "<<endl;
             deque <int> temp; 
             write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='l'){
            cout<<"int avec des list"<<endl;
            list<int> temp;
            write(vect,argv[1],temp);
        }
    }
    // cas entier non signé 
    else if (vect[0][0]=='u'){
        if (vect[1][0]=='v'){
            cout<< "on travaille avec vector unsigned int  "<<endl;
            vector<unsigned int> temp;
            write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='d'){
             deque <unsigned int> temp; 
             write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='l'){
            cout<<"Pb avec les lists pour le moment"<<endl;
        }
    }

    // cas float 
    else if (vect[0][0]=='f'){
        if (vect[1][0]=='v'){
            vector<float> temp;
            write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='d'){
             deque <float> temp; 
             write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='l'){
            cout<<"Pb avec les lists pour le moment"<<endl;
        }
    }
    // cas double 
    else if (vect[0][0]=='d'){
        if (vect[1][0]=='v'){
            vector<double> temp;
            write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='d'){
             deque <double> temp; 
             write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='l'){
            cout<<"Pb avec les lists pour le moment"<<endl;
        }
    }
    // cas char 
    else if (vect[0][0]=='d'){
        if (vect[1][0]=='v'){
            vector<char> temp;
            write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='l'){
             deque <char> temp; 
             write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='l'){
            cout<<"Pb avec les lists pour le moment"<<endl;
        }
    }
    // cas string
    else if (vect[0][0]=='s'){
        if (vect[1][0]=='v'){
            cout<<"str avec vector"<<endl;
            vector<string> temp;
            write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='d'){
            cout<<"str avec deque"<<endl;
             deque <string> temp; 
             write(vect,argv[1],temp);
        }
        else if (vect[1][0]=='l'){
            cout<<"Pb avec les lists pour le moment"<<endl;
        }
    }
    else{
        cout<<"error"<<endl;
    }

    return 0;
}