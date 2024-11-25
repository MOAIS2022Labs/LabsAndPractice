using System;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //полицейский - наследует насекомое
    public class PoliceAnt : Insect
    {
        public PoliceAnt()
        {
            NEEDFUL_FOOD_SIZE = 10;
            MAX_WAITING_TIME = 3;
            State = true; 
        }
        //метод Работа - возвращает коэффициент увеличения производительности работы муравьев - рабочих
        public int Work()
        {
            //если мертв - бросает исключение о смерти
            if (!State)
                throw new DeadException();
            return new Random().Next() % 3 + 1;
        }
    }
}
