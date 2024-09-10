using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //общий класс для исключений для насекомых
    public class InsectException : Exception
    {
        public InsectException() { }
        public InsectException(string message) : base(message) { }
    }
    //исключение, вызываемое при смерти насекомого
    public class DeadException : InsectException
    {
        public DeadException() { }
        public DeadException(string message) : base(message) { }
    }
}
