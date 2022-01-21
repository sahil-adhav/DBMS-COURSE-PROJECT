#include<bits/stdc++.h>
#include<fstream>
using namespace std;


void createTable(vector<string> query_create){
    // for(auto i: query_create){
    //     cout<<i<<endl;
    // }
    ofstream fout, fout_table;

    fout.open("schema.txt",std::ios_base::app);

    cout<<endl;
    string table_name = query_create[2]+".txt";
    fout_table.open(table_name, std::ios_base::app);

    for(int j = 3; j<query_create.size();j++){
        if(query_create[j] == "int"){
            fout<<query_create[2]<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<"#"<<query_create[j-1];
        }
        else if(query_create[j] == "decimal"){
            fout<<query_create[2]<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<"#"<<query_create[j-1];
        }
        else if(query_create[j].substr(0,4) == "char"){
            fout<<query_create[2]<<"#"<<query_create[j-1]<<"#"<<query_create[j]<<endl;
            fout_table<<"#"<<query_create[j-1];
        }
    }
    fout.close();
    fout_table.close();
    cout<<"Table created successfully!!"<<endl;
    cout<<endl;
}


void describeTable(vector<string> query_describe){

    string schema_path = "schema.txt";
    ifstream table(schema_path);
    string table_name = query_describe[1];
    cout<<endl;
    if(table.good()){
        bool exists = false;
        while(table){
        string line;
        getline(table, line);
        cout.flush();
        if(line.substr(0, table_name.length()) == table_name){
            exists = true;
            for(int i = table_name.length()+1; i<line.length();i++){
                if(line[i] == '#'){
                    cout<<"--";
                    i++;

                }
                cout<<line[i];

            }
            cout<<endl;
        }

        }
        if(exists == false){
            cout<<"Table does not exists in the database!"<<endl;
        }
        table.close();
    }
    cout<<endl;
}
void insertValues(vector<string> query_describe){

    string table_name = query_describe[2];
    string tname=query_describe[2]+".txt";
    ofstream insert_table;
    insert_table.open(tname,std::ios_base::app);


        if(insert_table){
           insert_table<<endl;

            //insert_table<<endl;
            for(int i=5;i<query_describe.size()-2;i++){
             if(query_describe[i] != ",")
             {
             insert_table<<"#"<<query_describe[i];
             }
            }

        }


        else{
            cout<<"Table does not exists in the database!"<<endl;
            }


        insert_table.close();
    }


void select(vector<string> query_select){
    
    bool all =false;
    if(query_select[1] ==  "*"){
        all = true;
    }
    vector<string> cols_name;
    vector<string> table_names;
    
    int from_index;
    int where_index;
    int end_index;

    for(int i =0;i < query_select.size();i++){
        if(query_select[i] == "from"){
            from_index =i;
        }
        if(query_select[i] == "where"){
            where_index = i;
        }
        if(query_select[i] == ";"){
            end_index = i;
        }
    }

    for(int i = from_index+1; i<where_index;i++){
        if(query_select[i] != ","){
            table_names.push_back(query_select[i]);
        }
    }

    if(all == true){
        for(int i =0;i<table_names.size();i++){
            string table_name = table_names[i];
            string table_path = table_name+".txt";
            ifstream table(table_path);
            cout<<endl;
            if(table.good()){
                string line;
                getline(table, line);
                cout.flush();

                stringstream ss(line);

                while (ss.good()) {
                    string substr;
                    getline(ss, substr, '#');
                    cols_name.push_back(substr);
                }


            table.close();
            }
            else{
                cout<<"Table does not exists in the database!"<<endl;
                return ;

            }
        }
    }
    else{
        for(int i = 1; i<from_index;i++){
            if(query_select[i] != ","){
                cols_name.push_back(query_select[i]);
            }
        }
    }

    /*for(int i =0;i<table_names.size();i++){
        cout<<table_names[i]<<" ";
    }
    cout<<endl;
    for(int i =0;i<cols_name.size();i++){
        cout<<cols_name[i]<<" ";
    }
    cout<<endl;*/
    vector<vector<string>> condition;
    vector<string> temp;
    bool andd = false;
    bool orr = false;
    for(int i = where_index+1; i< end_index;i++){
    if(query_select[i] != "and" && query_select[i] != "or"){
        temp.push_back(query_select[i]);
    }
    else{
        if(query_select[i] == "and"){
            andd = true;
        }
        else{
            orr = true;
        }
        condition.push_back(temp);
        temp.clear();
    }
    
    }
    condition.push_back(temp);
    vector<int> attr_indexes;

    vector<int> cols_index;

     string table_name = table_names[0];
            string table_path = table_name+".txt";
            ifstream table(table_path);
            cout<<endl;

            if(table.good()){

                int count =1;
                int count1 =1;
                vector<pair<string, int>> all_cols;
                while(!table.eof()){
                    string line;
                    getline(table, line);
                    cout.flush();
                    //cout<<line<<endl;           //print table line
                    stringstream ss(line);
                    vector<string> tuple;
                    while (ss.good()) {
                        string substr;
                        getline(ss, substr, '#');
                        tuple.push_back(substr);
                    }

                    if(count == 1){
                        for(int i =0;i<condition.size();i++){

                            for(int i1 =0;i1< tuple.size();i1++){
                                if((tuple[i1]) == condition[i][0]){
                                    attr_indexes.push_back(i1);
                                }
                            }
                        }

                        if(all == false){
                            for(int i = 0;i<cols_name.size();i++){
                                for(int i1 =0;i1<tuple.size();i1++){
                                   if(tuple[i1] == cols_name[i]){
                                       cols_index.push_back(i1);
                                   }
                                }
                            }
                        }
                        count++;

                    }

                    if(all == true){                //printing column names
                        if(count1 == 1){
                        for(int i2 =0;i2 < cols_name.size();i2++){
                                    cout<<cols_name[i2]<<"\t";
                                }
                                cout<<endl;
                                count1++;
                        }
                    }
                    else{
                        if(count1 == 1){
                        for(int i2 =0;i2 < cols_name.size();i2++){
                                    cout<<cols_name[i2]<<"\t";
                                }
                                cout<<endl;
                                count1++;
                        }
                    }

                    //cout<<condition[0].size();
                    int and_count = 0;
                    int or_count =0;

                    for(int j1 = 0;j1 < condition.size();j1++){

                        string oper = condition[j1][1];
                        string attr = condition[j1][0];
                        string value = condition[j1][2];
                        //cout<<attr<<" "<<oper<<" "<<value;
                    if(oper == "=="){
                        if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(tuple[attr_indexes[j1]] == value){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(tuple[attr_indexes[j1]] == value){

                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(tuple[attr_indexes[j1]] == value){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }


                        }
                        else{
                             if(andd == true){
                                 if(tuple[attr_indexes[j1]] == value){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    if(tuple[attr_indexes[j1]] == value){

                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;


                                }
                            }
                            else{
                                if(tuple[attr_indexes[j1]] == value){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }




                        }

                    }
                    else if(oper == "!="){
                        if(count1 == 2){
                            continue;
                            count1++;
                        }

                        if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(tuple[attr_indexes[j1]] != value){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(tuple[attr_indexes[j1]] != value){

                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(tuple[attr_indexes[j1]] != value){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }


                        }
                        else{
                             if(andd == true){
                                 if(tuple[attr_indexes[j1]] != value){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    if(tuple[attr_indexes[j1]] != value){

                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;


                                }
                            }
                            else{
                                if(tuple[attr_indexes[j1]] != value){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }




                        }

                    }

                    else if(oper == ">="){
                        stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{

                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }



                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(getValue >= value1){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){            // 1
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                    }
                                    else{
                                        and_count++;
                                    }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue >= value1){

                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue >= value1){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }


                        }
                        else{
                             if(andd == true){
                                 if(getValue >= value1){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    if(getValue >= value1){

                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;


                                }
                            }
                            else{
                                if(getValue >= value1){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }




                        }
                    }
                    else if(oper == "<="){
                            stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{

                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }



                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(getValue <= value1){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue <= value1){

                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue <= value1){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }


                        }
                        else{
                             if(andd == true){
                                 if(getValue <= value1){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    if(getValue <= value1){

                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;


                                }
                            }
                            else{
                                if(getValue <= value1){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }




                        }

                    }

                    else if(oper == ">"){
                         stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{

                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }



                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(getValue > value1){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue > value1){

                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue > value1){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }


                        }
                        else{
                             if(andd == true){
                                 if(getValue > value1){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    if(getValue > value1){

                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;


                                }
                            }
                            else{
                                if(getValue > value1){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }




                        }

                    }
                    else if(oper == "<"){
                        stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{

                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }



                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(getValue < value1){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue < value1){

                                                for(int i2 = 0; i2< tuple.size();i2++){
                                                    cout<<tuple[i2]<<"\t";
                                                }
                                                cout<<endl;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue < value1){
                                    for(int i2 = 0; i2< tuple.size();i2++){
                                        cout<<tuple[i2]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }


                        }
                        else{
                             if(andd == true){
                                 if(getValue < value1){

                                    if(and_count == condition.size() -1 ){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    if(getValue < value1){

                                               for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                                break;


                                }
                            }
                            else{
                                if(getValue < value1){
                                    for(int i2 = 0; i2< cols_index.size();i2++){
                                        cout<<tuple[cols_index[i2]]<<"\t";
                                    }
                                    cout<<endl;
                                }
                            }




                        }


                    }
                    }





                }

            }





    }

void deleteValue(vector<string> query_select){

    bool all =true;
    
    vector<string> cols_name;
    vector<string> table_names;

    int from_index;
    int where_index;
    int end_index;

    for(int i =0;i < query_select.size();i++){
        if(query_select[i] == "from"){
            from_index =i;
        }
        if(query_select[i] == "where"){
            where_index = i;
        }
        if(query_select[i] == ";"){
            end_index = i;
        }
    }

    for(int i = from_index+1; i<where_index;i++){
        if(query_select[i] != ","){
            table_names.push_back(query_select[i]);
        }
    }

    if(all == true){
        for(int i =0;i<table_names.size();i++){
            string table_name = table_names[i];
            string table_path = table_name+".txt";
            ifstream table(table_path);
            cout<<endl;
            if(table.good()){
                string line;
                getline(table, line);
                cout.flush();

                stringstream ss(line);

                while (ss.good()) {
                    string substr;
                    getline(ss, substr, '#');
                    cols_name.push_back(substr);
                }


            table.close();
            }
            else{
                cout<<"Table does not exists"<<endl;
                return ;

            }
        }
    }
    else{
        for(int i = 1; i<from_index;i++){
            if(query_select[i] != ","){
                cols_name.push_back(query_select[i]);
            }
        }
    }

    // for(int i =0;i<table_names.size();i++){
    //     cout<<table_names[i]<<" ";
    // }
    // cout<<endl;
    // for(int i =0;i<cols_name.size();i++){
    //     cout<<cols_name[i]<<" ";
    // }
    // cout<<endl;
    vector<vector<string>> condition;
    vector<string> temp;
    bool andd = false;
    bool orr = false;
    for(int i = where_index+1; i< end_index;i++){
    if(query_select[i] != "and" && query_select[i] != "or"){
        temp.push_back(query_select[i]);
    }
    else{
        if(query_select[i] == "and"){
            andd = true;
        }
        else{
            orr = true;
        }
        condition.push_back(temp);
        temp.clear();
    }
    // if(i - where_index == 3){
    //     condition.push_back(temp);
    //     temp.clear();
    // }

        //condition.push_back(query_select[i]);
    }
    condition.push_back(temp);

    // for(int i =0 ;i<condition.size();i++){    //print conditions
    //     for(int j =0;j<condition[i].size();j++){
    //         cout<<condition[i][j] <<" ";

    //     }
    //     cout<<endl;
    // }

    // for(int i=0;i<condition.size();i++){
    //     cout<<condition[i]<<" ";
    // }

    //string attr = condition[0];
    //int attr_index;

    vector<int> attr_indexes;


    // string oper = condition[1];
    // string value = condition[2];

    vector<int> cols_index;
    ofstream temporary;
    temporary.open("temp.txt");
    
     string table_name = table_names[0];
            string table_path = table_name+".txt";
            ifstream table(table_path);
            cout<<endl;

            if(table.good()){

                int count =1;
                int count1 =1;
                vector<pair<string, int>> all_cols;
                while(!table.eof()){
                    bool del = false;
                    string line;
                    getline(table, line);
                    cout.flush();
                    //cout<<line<<endl;           //print table line
                    stringstream ss(line);
                    vector<string> tuple;
                    while (ss.good()) {
                        string substr;
                        getline(ss, substr, '#');
                        tuple.push_back(substr);
                    }




                    if(count == 1){
                        for(int i =0;i<condition.size();i++){

                            for(int i1 =0;i1< tuple.size();i1++){
                                if((tuple[i1]) == condition[i][0]){
                                    attr_indexes.push_back(i1);
                                }
                            }
                        }

                        if(all == false){
                            for(int i = 0;i<cols_name.size();i++){
                                for(int i1 =0;i1<tuple.size();i1++){
                                   if(tuple[i1] == cols_name[i]){
                                       cols_index.push_back(i1);
                                   }
                                }
                            }
                        }
                        count++;

                    }
                   
                    int and_count = 0;
                    int or_count =0;

                    for(int j1 = 0;j1 < condition.size();j1++){

                        string oper = condition[j1][1];
                        string attr = condition[j1][0];
                        string value = condition[j1][2];
                        //cout<<attr<<" "<<oper<<" "<<value;
                    if(oper == "=="){
                        if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(tuple[attr_indexes[j1]] == value){

                                    if(and_count == condition.size() -1 ){
                                    del = true;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(tuple[attr_indexes[j1]] == value){

                                                del = true;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(tuple[attr_indexes[j1]] == value){
                                    //cout<<line<<endl;
                                    del = true;
                                    
                                }
                            }


                        }
                        

                    }
                    else if(oper == "!="){
                        if(count1 == 2){
                            continue;
                            count1++;
                        }

                        if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(tuple[attr_indexes[j1]] != value){

                                    if(and_count == condition.size() -1 ){
                                    del = true;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(tuple[attr_indexes[j1]] != value){

                                                del = true;

                                                break;
                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(tuple[attr_indexes[j1]] != value){
                                    del = true;
                                }
                            }


                        }
                       
                    }

                    else if(oper == ">="){
                        stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{

                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }



                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(getValue >= value1){

                                    if(and_count == condition.size() -1 ){
                                    del = true;
                                    }
                                    else{
                                        and_count++;
                                    }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue >= value1){

                                                del = true;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue >= value1){
                                    del = true;
                                }
                            }


                        }
                        
                    }
                    else if(oper == "<="){
                            stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{

                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }



                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(getValue <= value1){

                                    if(and_count == condition.size() -1 ){
                                    del = true;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue <= value1){

                                                del = true;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue <= value1){
                                    del = true;
                                }
                            }


                        }
                        
                    }

                    else if(oper == ">"){
                         stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{

                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }



                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(getValue > value1){

                                    if(and_count == condition.size() -1 ){
                                    del = true;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue > value1){

                                                del = true;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue > value1){
                                    del = true;
                                }
                            }


                        }
                        

                    }
                    else if(oper == "<"){
                        stringstream decimal(tuple[attr_indexes[j1]]);
                        stringstream decimal_value(value);
                        double value1 =0 ;
                        double getValue = 0;
                        try{

                        decimal >> getValue;
                        decimal_value >> value1;
                        }
                        catch(exception e){
                            cout<<"error"<<endl;
                        }



                        if(getValue == 0 || value1 == 0){
                            break;
                        }
                            if(all == true){
                            //cout<<andd;
                            if(andd == true){

                                if(getValue < value1){

                                    if(and_count == condition.size() -1 ){
                                    del = true;
                                }
                                else{
                                    and_count++;
                                }
                                }
                            }
                            else if(orr == true){
                                    //cout<<"\n"<<tuple[attr_indexes[j1]]<<" "<<value;
                                    if(getValue < value1){

                                                del = true;
                                                break;


                                }

                                //cout<<or_count<<endl;
                            }

                            else{
                                //cout<<tuple[attr_indexes[j1]]<<" "<<value<<endl;
                                if(getValue < value1){
                                    del = true;
                                }
                            }


                        }
                        


                    }
                    }



                    if(del == false){
                        //cout<<line<<endl;
                    temporary<<line << endl;
                    }
                    
                }

            }

        
        temporary.close();
        table.close();
        char new_name[table_path.length()] ;
        strcpy(new_name, table_path.c_str());
        int status;
        // for(int i =0;i<table_path.length();i++){
        //     cout<<new_name[i];
        // }
        // cout<<table_path.length()<<endl;
        status = remove(new_name);
        
        int value;
        value = rename("temp.txt" , new_name);
        
        

    }

void update(vector<string> query_update){

string data,data2;
int set_index,where_index,end_index;
vector<vector<string>> tuple;
ofstream fout;
fstream table(query_update[1]+".txt");

if(table.is_open()){
getline (table,data);
vector<string> fields;
string str="";
for(int i=0;i<data.length();i++){
      if(data[i]!='#'){
        str=str+data[i];
        }
        if(data[i]=='#' && str!="" || i==data.length()-1){
        fields.push_back(str);
        str="";
       }
       }
       int field_length=fields.size();
       //cout<<field_length;
       int num_rows=0;
       while(!table.eof()){
        getline(table,data2);
        stringstream row(data2);
        vector<string> values;
        string substr;
        while (getline(row,substr,'#'))
           
         { 
         
           values.push_back(substr);
         }
         values.erase(values.begin()); 
         //for(int i=0;i<values.size();i++){
           // cout<<values[i]<<" ";
        // }
          
         tuple.push_back(values);
         for(int i=0;i<values.size();i++){
           // cout<<tuple[num_rows][i]<<" ";
         }
         num_rows++;
         }
         //cout<<num_rows;
         //for(int i=0;i<num_rows;i++){
            //for(int j=0;j<field_length;j++)
               // cout<<tuple[i][j]<<" ";
            //cout<<endl;

        // }
         for(int i=0;i<query_update.size();i++){
        if(query_update[i]=="set")
            set_index=i;
        else if(query_update[i]=="where")
            where_index=i;
        else if(query_update[i]==";")
             end_index=i;

         }

       map<int,vector<string>> attributes;
       vector<pair<int,vector<string>>> conditions;
       int c_index=set_index+1;
       bool exec=true;

       for(int i=set_index+1;i<where_index;i++){
        int col_num;
        if(exec){
        for(int j=0;j<fields.size();j++){
            if(fields[j]==query_update[c_index]){
                col_num=j;
                exec=false;
                break;
            }
            }
        }
       if(query_update[i]!=","){
        attributes[col_num].push_back(query_update[i]);
        } 
        
       if(query_update[i] == "," || i==where_index-1){
           exec=true;
           c_index+=4;
                   
         } 
                           
         }
         //for(auto i:attributes){
           // cout<<i.first<<" ";
            //for(auto j :i.second)
               // cout<<j<<" ";
            //cout<<endl;
       // }
        exec=true;
        pair<int,vector<string>> p;
        vector<string> v;
        for(int i=where_index+1;i<end_index;i++){
        int col_num;
        if(exec){
        for(int j=0;j<fields.size();j++){
            if(fields[j]==query_update[c_index]){
                col_num=j;
                exec=false;
                break;
            }
            }
        }
       if(query_update[i]!="and" && query_update[i]!="or"){
        v.push_back(query_update[i]);
        } 
        //for(auto k:v){
            //cout<<k<<" ";
        //}
        if(query_update[i] == "and" || query_update[i]=="or" || i==end_index-1){
        
        p=make_pair(col_num,v);
       
        conditions.push_back(p);
           
           exec=true;
           c_index+=4;
           v.clear();
                         
         } 
                           
         }
         //for(auto i:conditions){
            //cout<< i.first<<" ";
            //for(auto j:i.second){
              //  cout<<j<<" ";
           // }
           // cout<<endl;
        // }
        string condition; 
       if(where_index+4 != end_index){  
       condition=query_update[where_index+4];
       }
       else{
        condition="none";
       } 
        
       
      if(condition=="and"|| condition=="none"){
       for(int i=0;i<num_rows;i++){
        bool check=true;
        for(auto j:conditions){
            bool flag=false;
            int co_index=j.first;
            //cout<<co_index<<endl;
            //cout<<tuple[i][co_index];
            if(j.second[1]=="="){
              if(tuple[i][co_index]==j.second[2]){
               flag=true;
              } 
            }
            else if(j.second[1]=="!="){
             if(tuple[i][co_index]!=j.second[2]){
               flag=true;
              }  
            }
            else if(j.second[1]==">"){
                int x=stoi(tuple[i][co_index]);
                int y=stoi(j.second[2]);
                if(x>y){
                    flag=true;
                }
            }
            else if(j.second[1]==">="){
                int x=stoi(tuple[i][co_index]);
                int y=stoi(j.second[2]);
                if(x>=y){
                    flag=true;
                }
            }
            else if(j.second[1]=="<"){
                int x=stoi(tuple[i][co_index]);
                int y=stoi(j.second[2]);
                if(x<y){
                    flag=true;
                }
            } 

            else if(j.second[1]=="<="){
                int x=stoi(tuple[i][co_index]);
                int y=stoi(j.second[2]);
                if(x<=y){
                    flag=true;
                }
            } 

            //cout<<flag<<" ";
            if(flag==false){
                check=false;
                break;
               }

        } 
        
        //cout<<check<<endl;
        if(check==true){
         for(auto it:attributes){
            int index=it.first;
            tuple[i][index]=it.second[2];

         } 

        }
        
         } 
          for(int i=0;i<num_rows;i++){
            for(int j=0;j<field_length;j++)
               cout<<tuple[i][j]<<" ";
            cout<<endl;

         }
       }   
              
       else if(condition=="or"){ 
        for(int i=0;i<num_rows;i++){
         bool check=false;   
        for(auto j:conditions){
            bool flag=false;
            int co_index=j.first;
            //cout<<co_index<<endl;
            //cout<<tuple[i][co_index];
            if(j.second[1]=="="){
              if(tuple[i][co_index]==j.second[2]){
               flag=true;
              } 
            }
            else if(j.second[1]=="!="){
             if(tuple[i][co_index]!=j.second[2]){
               flag=true;
              }  
            }
            else if(j.second[1]==">"){
                int x=stoi(tuple[i][co_index]);
                int y=stoi(j.second[2]);
                if(x>y){
                    flag=true;
                }
            }
            else if(j.second[1]==">="){
                int x=stoi(tuple[i][co_index]);
                int y=stoi(j.second[2]);
                if(x>=y){
                    flag=true;
                }
            }
            else if(j.second[1]=="<"){
                int x=stoi(tuple[i][co_index]);
                int y=stoi(j.second[2]);
                if(x<y){
                    flag=true;
                }
            } 

            else if(j.second[1]=="<="){
                int x=stoi(tuple[i][co_index]);
                int y=stoi(j.second[2]);
                if(x<=y){
                    flag=true;
                }
            } 

            //cout<<flag<<" ";
      
            if(flag==true){
            for(auto it:attributes){
            int index=it.first;
            tuple[i][index]=it.second[2];
            //cout<<tuple[i][index];
               }

        } 
        
        //cout<<check<<endl;
        //if(check==true){
         //for(auto it:attributes){
         //   int index=it.first;
          //  tuple[i][index]=it.second[2]; 
        // } 

        }
        
         } 
         
         for(int i=0;i<num_rows;i++){
            for(int j=0;j<field_length;j++)
                cout<<tuple[i][j]<<" ";
            cout<<endl;
        }
       }
       fout.open("temp.txt",std::ios_base::app);
       for(int i=0;i<field_length;i++){
        fout<<"#"<<fields[i];
       }
       fout<<endl;
       for(int i=0;i<num_rows;i++){
            for(int j=0;j<field_length;j++)
                fout<<"#"<<tuple[i][j];
            if(i!=num_rows-1)
                fout<<endl;
        }
        fout.close();
        table.close();
        string table_name=query_update[1]+".txt";
        const char *table = table_name.c_str();
        remove(table);
        rename("temp.txt",table);
       
}
else{
   cout<<"Table does not exist";

}

}

void helpp(vector<string> query_help){
 

 if(query_help[1]=="tables"){
 ifstream schema("schema.txt");
 set<string> check;
 if(schema){
 while(!schema.eof()){
   string data,tables="";
   getline(schema,data);
   for(int i=0;i<data.length();i++){
    if(data[i]=='#'){
        break;
    }
    tables=tables+data[i];
   }
   check.insert(tables); 
   
    } 
    for(auto i:check){
        cout<<i<<endl;
    }
    schema.close();
}
  else{
   cout<<"NO Tables found";
  }
 }
 else{
    if(query_help[1]=="create"){
     cout<<"This statement is used to create tables in sql.\n\n";
     cout<<"It is used in the following way as given below.\n\n";
     cout<<"create table table_name (attr1 , attr1 type , attr2 , attr2 type..) ; \n";

    }

    else if(query_help[1]=="drop"){
    cout<<"This statement is used to drop the tables from the sql.\n\n";
    cout<<"It is used in the following way as given below.\n\n";
    cout<<"drop table table_name ;\n";
    }
    else if(query_help[1]=="select"){
    cout<<"This statement is used to select tuples from tables with specified conditions in sql.\n\n";
    cout<<"It is used in the following way as given below.\n\n";
    cout<<"select attribute_list from table _list where condition_list ; \n"; 
    }
     else if(query_help[1]=="insert"){
     cout<<"This statement is used to insert data into the tables in sql.\n\n";
     cout<<"It is used in the following way as given below.\n\n";
     cout<<"insert into table_name values (val1 , val2 ,... ); \n";
     }
     else if(query_help[1]=="delete"){
     cout<<"This statement is used to delete tables in sql.\n\n";
     cout<<"It is used in the following way as given below.\n\n";
     cout<<"delete from table_name where condition_list ; \n";
     }
     else if(query_help[1]=="update"){
      cout<<"This statement is used to update the values in the table in sql.\n\n";
     cout<<"It is used in the following way as given below.\n\n";
     cout<<"update table_name set attr1 = val1 ,attr2 = val2 where condition_list ; \n";
     }

 } 

 


} 

void drop(vector<string> drop_query){

string table=drop_query[1];
string table_name=table+".txt";
const char *table_names = table_name.c_str();
remove(table_names);
ofstream fout;
fout.open("temp.txt",std::ios_base::app);
ifstream schema("schema.txt");
while(schema){
    string data,temp="";
    getline(schema,data);
    for(int i=0;i<data.length();i++){
        if(data[i]=='#')
            break;
        temp=temp+data[i];
    }
    if(temp!=table){
        fout<<data;
    } 
    fout<<endl;
} 
schema.close();
string schema_path="schema.txt";
const char *schema1 = schema_path.c_str();
remove(schema1);
fout.close();
rename("temp.txt","schema.txt"); 
}
int main(){

    // system("CLS");
    string a;
    getline(cin,a);
    stringstream s1(a);
    string s2;
    vector<string> query;

    while(s1>>s2){
        query.push_back(s2);

    }

    while(query[0] != "quit"){


        if(query[0] == "create"){
            createTable(query);
        }
        else if(query[0] == "describe"){
            describeTable(query);
            }
         else if(query[0] == "insert"){
            insertValues(query);
        }
        else if(query[0] ==  "select"){
            select(query);
            cout<<endl;
        }
        else if(query[0] == "update"){
             update(query);
        }
        else if(query[0] == "delete"){
            deleteValue(query);
        } 
        else if(query[0] == "help"){
            helpp(query);
        }
        else if(query[0] == "drop"){
            drop(query);
        }

        query.clear();
        string a;
        getline(cin,a);
        stringstream s1(a);
        string s2;


        while(s1>>s2){
            query.push_back(s2);

        }

    }
return 0;
}
