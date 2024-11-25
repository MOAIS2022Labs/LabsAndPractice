using System;

namespace OS_lab1
{
    //класс для взаимодействия с формой
    public class Writer
    {
        //делегат Action, хранит задаваемую лямбду с аргументом string
        public Action<string> write;
        //собственно конструктор
        public Writer(Action<string> write) { this.write = write; }
    }
}
