namespace Seminar2
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dgvComputers = new System.Windows.Forms.DataGridView();
            this.dgvDesks = new System.Windows.Forms.DataGridView();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvComputers)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvDesks)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvComputers
            // 
            this.dgvComputers.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvComputers.Location = new System.Drawing.Point(12, 227);
            this.dgvComputers.Name = "dgvComputers";
            this.dgvComputers.RowTemplate.Height = 24;
            this.dgvComputers.Size = new System.Drawing.Size(523, 150);
            this.dgvComputers.TabIndex = 0;
            // 
            // dgvDesks
            // 
            this.dgvDesks.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvDesks.Location = new System.Drawing.Point(12, 12);
            this.dgvDesks.Name = "dgvDesks";
            this.dgvDesks.RowTemplate.Height = 24;
            this.dgvDesks.Size = new System.Drawing.Size(523, 150);
            this.dgvDesks.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(630, 182);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 28);
            this.button1.TabIndex = 2;
            this.button1.Text = "Update DB";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.dgvDesks);
            this.Controls.Add(this.dgvComputers);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load_1);
            ((System.ComponentModel.ISupportInitialize)(this.dgvComputers)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvDesks)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvComputers;
        private System.Windows.Forms.DataGridView dgvDesks;
        private System.Windows.Forms.Button button1;
    }
}

