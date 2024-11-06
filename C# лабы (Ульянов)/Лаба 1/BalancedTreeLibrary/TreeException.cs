using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1Tree
{
    public class TreeException : Exception
    {
        public TreeException(string message) : base(message) { }
    }
    public class ForbiddenTreeModificationException : TreeException
    {
        public ForbiddenTreeModificationException() : base("Попытка изменить неизменяемый объект!") { }
        public ForbiddenTreeModificationException(string message) : base(message) { }
    }
    public class InvalidTreeOperationException : TreeException
    {
        public InvalidTreeOperationException(string message) : base(message) { }
    }
    public class TreeOutOfRangeException : TreeException
    {
        public TreeOutOfRangeException(string message) : base(message) { }
    }
    

}
