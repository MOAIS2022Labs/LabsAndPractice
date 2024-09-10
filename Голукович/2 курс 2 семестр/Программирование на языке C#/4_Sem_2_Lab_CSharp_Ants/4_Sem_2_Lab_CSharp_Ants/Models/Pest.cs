using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //вредитель - наследует насекомое
    public class Pest: Insect
    {
        //не имеет никаких собственных методов - только ест
        public Pest()
        {
            NEEDFUL_FOOD_SIZE = 5;
            MAX_WAITING_TIME = 5;
            State = true; 
        }
    }
}
