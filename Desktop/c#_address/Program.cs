using System;
using System.Collections.Generic;
using System.Linq;

namespace SimpleAddressBook
{
    public class Person
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string PhoneNumber { get; set; }
        public List<string> Addresses { get; set; } = new List<string>();

        public Person(string firstName, string lastName, string phoneNumber)
        {
            FirstName = firstName;
            LastName = lastName;
            PhoneNumber = phoneNumber;
        }
    }

    class Program
    {
        private static List<Person> addressBook = new List<Person>();

        static void Main(string[] args)
        {
            string command = "";

            while (command.ToLower() != "退出")
            {
                Console.WriteLine("\n请输入命令 (添加, 列表, 移除, 搜索, 退出): ");
                command = Console.ReadLine().ToLower();

                switch (command)
                {
                    case "添加":
                        AddPerson();
                        break;
                    case "列表":
                        ListPeople();
                        break;
                    case "移除":
                        RemovePerson();
                        break;
                    case "搜索":
                        SearchPerson();
                        break;
                    case "退出":
                        Console.WriteLine("退出通讯录。");
                        break;
                    default:
                        Console.WriteLine("无效的命令。");
                        break;
                }
            }
        }

        private static void AddPerson()
        {
            Console.Write("请输入名字: ");
            string firstName = Console.ReadLine();

            Console.Write("请输入姓氏: ");
            string lastName = Console.ReadLine();

            Console.Write("请输入电话号码: ");
            string phoneNumber = Console.ReadLine();

            var person = new Person(firstName, lastName, phoneNumber);

            Console.Write("请输入地址 1: ");
            person.Addresses.Add(Console.ReadLine());

            Console.Write("请输入地址 2 (可选): ");
            string secondAddress = Console.ReadLine();
            if (!string.IsNullOrEmpty(secondAddress))
            {
                person.Addresses.Add(secondAddress);
            }

            addressBook.Add(person);
            Console.WriteLine($"{firstName} 已添加到通讯录。");
        }

        private static void ListPeople()
        {
            if (addressBook.Count == 0)
            {
                Console.WriteLine("通讯录为空。");
                return;
            }

            foreach (var person in addressBook)
            {
                PrintPerson(person);
            }
        }

        private static void RemovePerson()
        {
            Console.Write("请输入要移除的人的名字: ");
            string firstName = Console.ReadLine();

            var person = addressBook.FirstOrDefault(p => p.FirstName.Equals(firstName, StringComparison.OrdinalIgnoreCase));
            if (person != null)
            {
                addressBook.Remove(person);
                Console.WriteLine($"{firstName} 已从通讯录中移除。");
            }
            else
            {
                Console.WriteLine($"未在通讯录中找到 {firstName}。");
            }
        }

        private static void SearchPerson()
        {
            Console.Write("请输入要搜索的人的名字: ");
            string firstName = Console.ReadLine();

            var person = addressBook.FirstOrDefault(p => p.FirstName.Equals(firstName, StringComparison.OrdinalIgnoreCase));
            if (person != null)
            {
                PrintPerson(person);
            }
            else
            {
                Console.WriteLine($"未在通讯录中找到 {firstName}。");
            }
        }

        private static void PrintPerson(Person person)
        {
            Console.WriteLine($"名字: {person.FirstName}");
            Console.WriteLine($"姓氏: {person.LastName}");
            Console.WriteLine($"电话号码: {person.PhoneNumber}");
            Console.WriteLine($"地址 1: {person.Addresses.ElementAtOrDefault(0) ?? "无"}");
            Console.WriteLine($"地址 2: {person.Addresses.ElementAtOrDefault(1) ?? "无"}");
            Console.WriteLine(new string('-', 40));
        }
    }
}
