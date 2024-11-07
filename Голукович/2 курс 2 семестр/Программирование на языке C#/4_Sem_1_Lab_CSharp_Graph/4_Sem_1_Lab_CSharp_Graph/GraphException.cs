using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_1_Lab_CSharp
{
    //Класс, который наследуется всеми классами исключений графа
    public class GraphException : Exception
    {
        public GraphException() { }
        public GraphException(string message) : base(message) { }
    }

    //Используется для указания ошибки при попытке изменения графа, когда это не разрешено.
    public class DisabledChangeGraphException : GraphException
    {
        public DisabledChangeGraphException() { }
        public DisabledChangeGraphException(string message) : base(message) { }
    }

    //Используется для указания ошибки при попытке добавления вершины или ребра в граф, когда это не разрешено.
    public class DisabledAddGraphException : GraphException
    {
        public DisabledAddGraphException() { }
        public DisabledAddGraphException(string message) : base(message) { }
    }

    //Используется для указания ошибки при попытке удаления вершины или ребра из графа, когда это не разрешено.
    public class DisabledRemoveGraphException : GraphException
    {
        public DisabledRemoveGraphException() { }
        public DisabledRemoveGraphException(string message) : base(message) { }
    }

    //Используется для указания ошибки при попытке поиска вершины в графе, когда это не разрешено.
    public class DisabledFindGraphException : GraphException
    {
        public DisabledFindGraphException() { }
        public DisabledFindGraphException(string message) : base(message) { }
    }
}
