#include "main.h"
class Customer{

    public:
        string name;
        int age;
        Customer *next;

        Customer(){
            this->name  = "";
            this->age   =    0;
            this->next  =   nullptr;
        }
        Customer(string name, int age){
            this->name  =   name;
            this->age   =   age;
            this->next  =   nullptr;
        }
};
class Queue{
    public:
        Customer    *   head;
        Customer    *   tail;
        int count;

    Queue(){
        this->head  =   this->tail    =   nullptr;
        this->count =   0;
    }

    void push(Customer * customer)
    {
        if(count == 0)
        {
            this->head  =   customer;
            this->tail  =   customer;
            count++;
        }
        else
        {
            this->tail->next    =   customer;
            this->tail          =   customer;
            count++;
        }
    }

    Customer * top()
    {
        return this->head;
    }

    void pop()
    {
        if(count == 1)
        {
            // Customer * temp =   this->head;
            this->head = this->tail =   nullptr;
            count--;
            // delete temp;

        }
        else
        {
            Customer * temp =   this->head;
            this->head  =   this->head->next;
            temp->next  =   nullptr;
            count--;

        }
    }

    int size()
    {
        return this->count;
    }

};

class Stack{
    public:
        Customer    *   head;
        Customer    *   tail;
        int count = 0;
        Stack(){
            this->head    =   this->tail  = nullptr;
            this->count =   0;
        }

    void push(Customer * customer)
    {
        if(count == 0)
        {
            this->head  =   this->tail  =   customer;
            count++;
        }
        else
        {
            this->tail->next    =   customer;
            this->tail          =   customer;
            count++;
        }
    }

    Customer * top()
    {
        return this->tail;
    }

    void pop()
    {
        if(count == 1)
        {
            // Customer * temp =   this->head;
            this->head = this->tail =   nullptr;
            count--;
            // delete temp;
        }
        else{
            Customer * temp =   this->head;
            for(int i = 0; i<count-2; i++)
            {
                temp = temp->next;
            }
            this->tail  =   temp;
            temp    =   temp->next;
            this->tail->next    =   nullptr;
            count--;
            // delete temp;
        }
    }
    int size()
    {
        return this->count;
    }
};

void REGID(restaurant *r, int size, Queue *queue, Stack *stack, int id, string name, int age){
    if( age >= 16)
    {
        table *ptr =   r->recentTable;
        Customer *customer  =   new Customer(name, age);
        for(int i = 0; i < size ; i++)
        {
            if(ptr->ID == id)
            {
                if(ptr->name == "")
                {
                    ptr->name   =   name;
                    ptr->age    =   age;
                    r->recentTable  =   ptr;
                    stack->push(customer);
                    break;
                }
                else
                {
                    table *head =   ptr;
                    for(int i = 0; i<size; i++)
                    {
                        if(ptr->name == "")
                        {
                            stack->push(customer);
                            ptr->name   =   name;
                            ptr->age    =   age;
                            r->recentTable  =   ptr;

                            break;
                        }
                        ptr = ptr->next;
                    }
                    if(ptr == head)
                    {
                        if(queue->count <= size)
                        {
                            stack->push(customer);
                            queue->push(customer);
                        }
                    }
                }
                break;
            }
            ptr = ptr->next;
        }
    }
}

void REG(restaurant *r, int size, Queue *queue, Stack *stack, string name, int age){
    if(age >= 16)
    {
        table *ptr =   r->recentTable;
        Customer *customer  =   new Customer(name,age);
        int idmin = size;
        for(int i = 0; i < size; i++)
        {
            if(ptr->name == "" && ptr->ID <= idmin)
            {
                idmin = ptr->ID;
            }
            ptr = ptr->next;
        }
        if(idmin != size)
        {
            ptr = r->recentTable;
            for(int i = 0; i < size; i++)
            {
                if(ptr->ID == idmin)
                {
                    stack->push(customer);
                    ptr->name   =   name;
                    ptr->age    =   age;
                }
                ptr = ptr->next;
            }
        }
        else
        {
            if(queue->count <= size)
            {
                stack->push(customer);
                queue->push(customer);
            }
        }
    }
    
}

void REGM(restaurant *r, int size, string name, int age, int num){
    table *ptr =   r->recentTable;
    table *temp;
    int idMAx = 0;
    bool check = true;
    for(int i = 0; i<size; i++)
    {
        temp =   ptr;
        check = true;
        for(int j = 0; j<num; j++)
        {
            if(temp->name == "")
                check = true;
            else
            {
                check = false;
                break;
            }
            temp = temp->next;
        }
        if(check == true)
        {
            if(ptr->ID >= idMAx)
            {
                idMAx = ptr->ID;
            }
        }
        ptr = ptr->next;
    }
    if(idMAx !=0)
    {
        for(int i = 0; i<size; i++)
        {
            if(ptr->ID == idMAx)
            {
                for(int i = 0; i<num; i++)
                {
                    ptr->name = name;
                    ptr->age = age;
                    ptr = ptr->next;
                }
                break;
            }
            ptr = ptr->next;
        }
    }

}

void CLE(restaurant *r, int size, Stack *stack, Queue *queue, int id){
    table *ptr  =   r->recentTable;
    for(int i = 0; i<size; i++)
    {
        if(ptr->ID == id)
        {
            while (ptr->ID == id)
            {
                if(ptr->name != "")
                {
                    Stack *temp = new Stack();
                    while (stack->count)
                    {
                        if(stack->top()->name == ptr->name)
                        {
                            stack->pop();
                            break;
                        }
                        else
                        {
                            temp->push(stack->top());
                            stack->pop();
                        }
                    }
                    while (temp->count)
                    {
                        stack->push(temp->top());
                        temp->pop();
                    }
                    if(queue->count)
                    {
                        ptr->name   =   queue->top()->name;
                        ptr->age    =   queue->top()->age;
                        queue->pop();
                    }
                    else
                    {
                        ptr->name   =   "";
                        ptr->age    =   0;                  
                    }
                }
                ptr = ptr->next;
            }
            break;
        }
        ptr =   ptr->next;
    }
}

void PS(restaurant *r, int size, Stack *stack, int num){
    Stack *temp = new Stack();
    if(stack->count == 0)
    {
        cout<<"Empty"<<endl;
    }
    else if(!num || num > stack->count)
    {
        while (stack->count)
        {
            cout<<stack->top()->name<<endl;
            temp->push(stack->top());
            stack->pop();
        }
        while (temp->count)
        {
            stack->push(temp->top());
            temp->pop();
        }
    }
    else
    {
        while (num !=0)
        {
            cout<<stack->top()->name<<endl;
            temp->push(stack->top());
            stack->pop();
            num--;
        }
        while (temp->count)
        {
            stack->push(temp->top());
            temp->pop();
        }
    }

      
}

void PQ(restaurant *r, int size, Queue *queue, int num){
    if(queue->count == 0){
        cout<<"Empty"<<endl;
    }
    else if(!num || num > queue->count)
    {
        Queue *temp = new Queue();
        while (queue->count)
        {
            cout<<queue->top()->name<<endl;
            temp->push(queue->top());
            queue->pop();
        }
        while (temp->count)
        {
            queue->push(temp->top());
            temp->pop();
        }
    }
    else
    {
        Queue *temp = new Queue();
        while (queue->count)
        {
            if(num != 0)
            {
                cout<<queue->top()->name<<endl;
                num--;
            }
            temp->push(queue->top());
            queue->pop();
            
        }
        while (temp->count)
        {
            queue->push(temp->top());
            temp->pop();
        }
    }

}

void PT(restaurant *r, int size){
    string temp = "";
    table *ptr = r->recentTable;
    for(int i = 0; i<size; i++)
    {
        if(ptr->name != temp)
        {
            cout<<ptr->ID<<"-"<<ptr->name<<endl;
            temp = ptr->name;
        }
        ptr = ptr->next;
    }
}

void SQ(restaurant *r, int size, Queue *queue, int num){
    if(queue->count == 0)
    {
        cout<<"Empty"<<endl;
    }
    else
    {
        Customer *head = queue->head;
        Customer *temp = new Customer;
        string nametemp;
        int agetemp;

        while(head)
        {
            temp = head;
            while (temp)
            {
                if(temp->age >= head->age)
                {
                    nametemp    = head->name;
                    agetemp     = head->age;
                    head->name  =   temp->name;
                    head->age   =   temp->age;
                    temp->name  =   nametemp;
                    temp->age   =   agetemp;
                }
                temp    =   temp->next;
            }
            
            head = head->next;
        }
        head = queue->head;
        if(num > queue->count && num <= size)
        {
            while (head)
            {
                cout<<head->name<<endl;
                head = head->next;
            }
            
        }
        else if(num <= queue->count)
        {
            while (num!=0)
            {
                cout<<head->name<<endl;
                head = head->next;
                num--;
            }   
        }    
    }
}

void simulate(string filename, restaurant* r)
{
    string StrLine;
    int id, age, num;
    string name, func;
    int size = 0;
    table *temp = r->recentTable;
    while (1)
    {
        size++;
        temp = temp->next;
        if(temp == r->recentTable)
            break;
    }
    
    Queue *queue = new Queue();
    Stack *stack = new Stack();
    ifstream MyReadFile(filename);
    while (getline (MyReadFile, StrLine))
    {
        func = StrLine.substr(0, StrLine.find(" "));
        StrLine.erase(0, StrLine.find(" ") + 1);
        if(func == "REG")
        {
            name = StrLine.substr(0, StrLine.find(32)+1);
            if(StrLine.substr(StrLine.find(32)+1).find(32) < StrLine.length())
            {
                id =    stoi(StrLine.substr(0, StrLine.find(32)+1));
                StrLine = StrLine.substr(StrLine.find(32)+1);
                name = StrLine.substr(0, StrLine.find(32)+1);
                StrLine = StrLine.substr(StrLine.find(32)+1);
                age =   stoi(StrLine);
                REGID(r, size, queue, stack, id, name, age);
            }
            else
            {
                StrLine = StrLine.substr(StrLine.find(32)+1);
                age =   stoi(StrLine);
                REG(r, size, queue, stack, name, age);
            }

        }else if(func == "REGM"){
            name = StrLine.substr(0, StrLine.find(32)+1);
            StrLine = StrLine.substr(StrLine.find(32)+1);
            age =   stoi(StrLine.substr(0, StrLine.find(32)+1));
            StrLine = StrLine.substr(StrLine.find(32)+1);
            num =   stoi(StrLine);
            REGM(r, size, name, age, num);

        }else if(func == "CLE"){
            id = stoi(StrLine);
            CLE(r, size, stack,queue, id);

        }else if(func == "PS"){
            num = stoi(StrLine);
            PS(r, size, stack, num);

        }else if(func == "PQ"){
            num = stoi(StrLine);
            PQ(r, size, queue, num);

        }else if(func == "PT"){
            PT(r ,size);

        }else if(func == "SQ"){
            num = stoi(StrLine);
            SQ(r, size, queue, num);

        }else{
            continue;
        }
    }
    MyReadFile.close();
}

