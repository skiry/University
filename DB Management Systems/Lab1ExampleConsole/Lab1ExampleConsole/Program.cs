using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data;
using static System.Net.Mime.MediaTypeNames;

namespace Lab1Example
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {

            String conn = "Data Source = LAPTOP-8A3HVFCJ\\SQLEXPRESS ;" + "Initial Catalog = ITCompany ; Integrated Security = true";
            SqlConnection sqlconn = new SqlConnection(conn);

            try
            {
                Console.WriteLine("Welcome!");
                sqlconn.Open();
                Console.WriteLine("Connection open!");
                SqlCommand com1 = new SqlCommand("SELECT id, operating_system as OS FROM Computers", sqlconn);
                SqlDataReader reader = com1.ExecuteReader();
                if (reader.HasRows)
                {
                    while (reader.Read())
                    {
                        Console.WriteLine("{0}\t{1}", reader.GetInt32(0), reader.GetString(1));
                    }
                }
                reader.Close();     

                DataSet dset = new DataSet();
                SqlDataAdapter adapterComputers = new SqlDataAdapter("SELECT * FROM [Computers]", sqlconn);
                adapterComputers.Fill(dset);

                Console.WriteLine(dset.Tables.Count);

                SqlDataAdapter adapterDesks = new SqlDataAdapter("SELECT * FROM [Desks]", sqlconn);
                adapterDesks.Fill(dset);

                foreach (DataTable table in dset.Tables)
                {
                    foreach (DataRow row in table.Rows)
                    {
                        foreach (DataColumn column in table.Columns)
                        {
                            Console.WriteLine(row[column]);
                        }
                    }
                }
                //print contents of computers

                //DataRelation relation = new DataRelation("ComputersDesks", dset.Tables["Desks"].Columns["id"], dset.Tables["Computers"].Columns["desk_id"]);
                //dset.Relations.Add(relation);
            }
            catch
            {
                Console.WriteLine("Could not open connection!");
            }
            finally
            {
                sqlconn.Close();
            }
        }
    }
}
