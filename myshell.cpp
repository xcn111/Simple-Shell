#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
using namespace std;

string currentaddress;
string outputaddress;
int pid=1,fd[2];
int main() {
    pipe(fd);
    char cp[100];
    getcwd(cp,100);
    currentaddress=cp;
    while(1&&pid){
        cout<<currentaddress<<" >";
        string inputcommand;
        getline(cin,inputcommand);
        if(inputcommand.empty()||all_of(inputcommand.begin(), inputcommand.end(), ::isspace)) continue;
        vector<string>tokens;
        istringstream is(inputcommand);
        for(string token;is>>token;) tokens.push_back(token);

        if(tokens.front()=="myshell"){
            string batchfile=currentaddress+"/"+tokens.back();
            freopen(batchfile.c_str(),"r",stdin);
            continue;
        }

        bool run_in_background=tokens.back()=="&"?true:false;
        if(run_in_background) tokens.pop_back();

        ofstream fout;
        bool bout=false;
        if(tokens[tokens.size()-2]==">"){
            outputaddress=tokens.back();
            ifstream file(outputaddress);
            if(!file.good()){
                cout<<"file not exist"<<endl;
                continue;
            }
            fout.open(outputaddress);
            bout=true;
            tokens.pop_back();
            tokens.pop_back();
        } else if(tokens.size()>=2&&tokens[tokens.size()-2]==">>"){
            outputaddress=tokens.back();
            fout.open(outputaddress);
            bout=true;
            tokens.pop_back();
            tokens.pop_back();
        }
        
        if(tokens.size()>=2&&tokens[tokens.size()-2]=="<"){
            string inputaddress=tokens.back();
            ifstream file(inputaddress);
            if(!file.good()){
                cout<<"file not exist"<<endl;
                continue;
            }
            tokens.pop_back();
            tokens.pop_back();
            ifstream fin(inputaddress);
            while(getline(file, inputcommand)){ 
                istringstream is(inputcommand);
                for(string token;is>>token;) tokens.push_back(token);
            }
            fin.close();
        }

        if(tokens.front()=="cd"){
            if(run_in_background){
                pid=fork();
                if(pid==0){
                    if(tokens.size()>1) currentaddress=tokens.back();
                    close(fd[0]);
                    write(fd[1],currentaddress.c_str(),currentaddress.size()+1);
                    close(fd[1]);
                    exit(0);
                }
                else{
                    char buf[100]={};
                    close(fd[1]);
                    read(fd[0],buf,sizeof(buf));
                    close(fd[0]);
                    wait(NULL);
                    currentaddress=buf;
                }
            }
            else {
                if(tokens.size()>1) currentaddress=tokens.back();
            }
        }
        else if(tokens.front()=="clr"){
            system("clear");
        }
        else if(tokens.front()=="dir"){
            if(run_in_background){
                pid=fork();
                if(pid==0){
                    string cmd="dir ";
                    cmd+=currentaddress;
                    if(bout) cmd+=" > "+outputaddress;
                    system(cmd.c_str());
                    exit(0);
                }
                else wait(NULL);
            }
            else {
                string cmd="dir ";
                cmd+=currentaddress;
                if(bout) cmd+=" > "+outputaddress;
                system(cmd.c_str());
            }
        }
        else if(tokens.front()=="environ"){
            pid=fork();
            if(pid==0){
                if(bout) {
                    outputaddress="env > "+outputaddress;
                    char *oa=new char[outputaddress.size()+1];
                    strcpy(oa,outputaddress.c_str());
                    char *argv[] = {"sh", "-c", oa, NULL};
                    execvp("sh", argv);
                }
                else {char *args[]={"env",nullptr};execvp("env",args);}
                exit(0);
            }
            else wait(NULL);
        }
        else if(tokens.front()=="echo"){
            string output;
            for(int i=1;i<tokens.size();i++) output+=tokens[i]+" ";
            if(run_in_background){
                pid=fork();
                if(pid==0){
                    if(bout) output="echo "+output+" > "+outputaddress;
                    else output="echo "+output;
                    system(output.c_str());
                    exit(0);
                }
                else wait(NULL);
            }
            else {
                if(bout) output="echo "+output+" > "+outputaddress;
                else output="echo "+output;
                system(output.c_str());
            }
        }
        else if(tokens.front()=="help"){
            string output="more README";
            if(bout) output+=" > "+outputaddress;
            if(run_in_background){
                pid=fork();
                if(pid==0) {system(output.c_str());exit(0);}
                else wait(NULL);
            }
            else {
                system(output.c_str());
            }
        }
        else if(tokens.front()=="pause"){
            cout<<"Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<endl;
        }
        else if(tokens.front()=="quit") return 0;
    }
    return 0;
}