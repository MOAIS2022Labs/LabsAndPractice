using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //муравей рабочий - наследует насекомое
    public class WorkerAnt : Insect
    {
        public WorkerAnt()
        {
            NEEDFUL_FOOD_SIZE = 5;
            MAX_WAITING_TIME = 2;
            State = true; 
        }
        //метод работа - добавляет еду в хранилище в зависимости от коэффициента, который создают муравьи-полицейские
        public void Work(FoodStorage foodStorage, int k = 1)
        {
            //если мертв - исключение о смерти
            if (!State)
                throw new DeadException();
            //добавление еды в хранилище
            for (int i = 1; i <= k; ++i)
                foodStorage.Add(i * 10);
        }
    }
}
