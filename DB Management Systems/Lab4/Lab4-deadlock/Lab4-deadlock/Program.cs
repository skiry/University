using System;
using System.Threading;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;

namespace Deadlock
{
    class Program
    {
        private static void updateBookAuthor()
        {
            String connString = @"Data Source = LAPTOP-8A3HVFCJ\SQLEXPRESS; Initial Catalog = ITCompany; Integrated Security = SSPI";

            using (SqlConnection conn = new SqlConnection(connString))
            {
                conn.Open();

                int tryCount = 0;

                while (tryCount < 10)
                {
                    SqlTransaction transaction = conn.BeginTransaction("UpdateTransaction");
                    try
                    {

                        Console.WriteLine("Thread 1 wants to delete\n");
                        SqlCommand insertBookCommand = conn.CreateCommand();
                        insertBookCommand.Transaction = transaction;
                        insertBookCommand.CommandText = "DELETE FROM Computers WHERE id = 1";
                        insertBookCommand.ExecuteNonQuery();
                        Console.WriteLine("Thread 1 deleted\n");

                        Thread.Sleep(5000);

                        Console.WriteLine("Thread 1 wants to delete\n");
                        SqlCommand insertAuthorCommand = conn.CreateCommand();
                        insertAuthorCommand.Transaction = transaction;
                        insertAuthorCommand.CommandText = "DELETE FROM WorkTimes WHERE work_time = 8";
                        insertAuthorCommand.ExecuteNonQuery();
                        Console.WriteLine("Thread 1 deleted\n");

                        transaction.Commit();
                        break;
                    }
                    catch (System.Data.SqlClient.SqlException ex)
                    {
                        tryCount += 1;
                        Console.WriteLine(ex.Message);
                        transaction.Rollback();
                    }
                }

                conn.Close();
            }

            Console.WriteLine("Thread 1 finished");
        }

        private static void updateAuthorBook()
        {
            String connString = @"Data Source = LAPTOP-8A3HVFCJ\SQLEXPRESS; Initial Catalog = ITCompany; Integrated Security = SSPI";



            using (SqlConnection conn = new SqlConnection(connString))
            {
                conn.Open();

                int tryCount = 0;

                while (tryCount < 10)
                {
                    SqlTransaction transaction = conn.BeginTransaction("UpdateTransaction");
                    try
                    {
                        Console.WriteLine("Thread 2 wants to delete\n");
                        SqlCommand insertAuthorCommand = conn.CreateCommand();
                        insertAuthorCommand.Transaction = transaction;
                        insertAuthorCommand.CommandText = "DELETE FROM WorkTimes WHERE work_time = 8";
                        insertAuthorCommand.ExecuteNonQuery();
                        Console.WriteLine("Thread 2 deleted\n");

                        Thread.Sleep(5000);

                        Console.WriteLine("Thread 2 wants to delete\n");
                        SqlCommand insertBookCommand = conn.CreateCommand();
                        insertBookCommand.Transaction = transaction;
                        insertBookCommand.CommandText = "DELETE FROM Computers WHERE id = 1";
                        insertBookCommand.ExecuteNonQuery();
                        Console.WriteLine("Thread 2 deleted\n");
                        transaction.Commit();
                        break;
                    }
                    catch (System.Data.SqlClient.SqlException ex)
                    {
                        tryCount += 1;
                        Console.WriteLine(ex.Message);
                        transaction.Rollback();
                    }
                }
                conn.Close();
            }

            Console.WriteLine("Thread 2 finished");
        }

        public static void Main(String[] args)
        {
            Thread firstThread = new Thread(updateBookAuthor);
            Thread secondThread = new Thread(updateAuthorBook);
            firstThread.Start();
            secondThread.Start();
        }
    }
}