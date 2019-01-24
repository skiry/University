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
        SqlDataAdapter daDesks, daComputers;
        DataSet ds;
        BindingSource bsDesks, bsComputers;
        SqlCommandBuilder cb;
        private void button1_Click(object sender, EventArgs e)
        {
            daComputers.Update(ds, "Computers");
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {
            conn = new SqlConnection(@"Data Source = LAPTOP-8A3HVFCJ\SQLEXPRESS; Initial Catalog = ITCompany; Integrated Security = SSPI");
            daComputers = new SqlDataAdapter("SELECT * FROM Computers", conn);
            daDesks = new SqlDataAdapter("SELECT * FROM Desks", conn);
            ds = new DataSet();
            daComputers.Fill(ds, "Computers");
            daDesks.Fill(ds, "Desks");   
            cb = new SqlCommandBuilder(daComputers);

            ds.Relations.Add(
                "FK_Desks_Computers",
                ds.Tables["Desks"].Columns["team_id"],
                ds.Tables["Computers"].Columns["desk_id"]
                );

            bsDesks = new BindingSource();
            bsDesks.DataSource = ds;
            bsDesks.DataMember = "Desks";

            bsComputers = new BindingSource();
            bsComputers.DataSource = bsDesks;
            bsComputers.DataMember = "FK_Desks_Computers";

            dgvComputers.DataSource = bsComputers;
            dgvDesks.DataSource = bsDesks;
        }

        public Form1()
        {
            InitializeComponent();
        }
    }
}
