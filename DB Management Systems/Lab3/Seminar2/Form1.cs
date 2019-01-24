using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Configuration;

namespace Seminar2
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter daParentTable, daChildTable;
        DataSet ds;
        BindingSource bsParentTable, bsChildTable;
        SqlCommandBuilder cb;
        string childTable = ConfigurationManager.AppSettings["childTable"];
        private void button1_Click(object sender, EventArgs e)
        {
            daChildTable.Update(ds, childTable);
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
            string connStr = ConfigurationManager.ConnectionStrings["StudentInternships"].ConnectionString;
            Console.Write(connStr);
            conn = new SqlConnection(connStr);

            string parentTable = ConfigurationManager.AppSettings["parentTable"];
            string parentKey = ConfigurationManager.AppSettings["parentKey"];
            string childKey = ConfigurationManager.AppSettings["childKey"];

            daChildTable = new SqlDataAdapter("SELECT * FROM " + childTable, conn);
            daParentTable = new SqlDataAdapter("SELECT * FROM " + parentTable, conn);
            ds = new DataSet();
            daChildTable.Fill(ds, childTable);
            daParentTable.Fill(ds, parentTable);   
            cb = new SqlCommandBuilder(daChildTable);

            ds.Relations.Add(
                "FK_Desks_Computers",
                ds.Tables[parentTable].Columns[parentKey],
                ds.Tables[childTable].Columns[childKey]
                );

            bsParentTable = new BindingSource();
            bsParentTable.DataSource = ds;
            bsParentTable.DataMember = parentTable;

            bsChildTable = new BindingSource();
            bsChildTable.DataSource = bsParentTable;
            bsChildTable.DataMember = "FK_Desks_Computers";

            dgvComputers.DataSource = bsChildTable;
            dgvDesks.DataSource = bsParentTable;
        }

        public Form1()
        {
            InitializeComponent();
        }
    }
}
