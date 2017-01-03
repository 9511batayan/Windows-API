using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Win32AP_iphonebutton
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
           // GraphicsPathの作成 
           System.Drawing.Drawing2D.GraphicsPath path =
                new System.Drawing.Drawing2D.GraphicsPath();
           //円を描く(ホームボタン)
           path.AddEllipse(new Rectangle(3, 3, 57, 57));
           hombtn.Region = new Region(path);   //コントロールの形を変更

            //ボタンを描くための座標を指定
           Point[] points = {
        new Point(9, 3),
        new Point(3, 10),
        new Point(3, 49),
        new Point(10, 55),
        new Point(49, 55),
        new Point(55, 49),
        new Point(55,10),
        new Point(49,3)
                            };
       
           //GraphicsPathの作成
           System.Drawing.Drawing2D.GraphicsPath path1 =
              new System.Drawing.Drawing2D.GraphicsPath();

            //point内の各点を曲線で結ぶ
            path1.AddClosedCurve(points, 0.2F);

            //各ボタンコントロールの形を変更
           btn1.Region = new Region(path1);
           btn2.Region = new Region(path1);
           btn3.Region = new Region(path1);
           btn4.Region = new Region(path1);
           btn5.Region = new Region(path1);
           btn6.Region = new Region(path1);
           btn7.Region = new Region(path1);
           btn8.Region = new Region(path1);
           btn9.Region = new Region(path1);
           btn10.Region = new Region(path1);
           btn11.Region = new Region(path1);
           btn12.Region = new Region(path1);

           //各Labelの親コントロールをPictureBox1とする
           pictureBox1.Controls.Add(label1);
           pictureBox1.Controls.Add(label2);
           pictureBox1.Controls.Add(label3);
           pictureBox1.Controls.Add(label4);
           pictureBox1.Controls.Add(label5);
           pictureBox1.Controls.Add(label6);
           pictureBox1.Controls.Add(label7);
           pictureBox1.Controls.Add(label8);
           pictureBox1.Controls.Add(label9);
           pictureBox1.Controls.Add(label10);
           pictureBox1.Controls.Add(label11);
           pictureBox1.Controls.Add(label12);

           //各ボタンの親コントロールをPictureBox1とする
           pictureBox1.Controls.Add(btn1);
           pictureBox1.Controls.Add(btn2);
           pictureBox1.Controls.Add(btn3);
           pictureBox1.Controls.Add(btn4);
           pictureBox1.Controls.Add(btn5);
           pictureBox1.Controls.Add(btn6);
           pictureBox1.Controls.Add(btn7);
           pictureBox1.Controls.Add(btn8);
           pictureBox1.Controls.Add(btn9);
           pictureBox1.Controls.Add(btn10);
           pictureBox1.Controls.Add(btn11);
           pictureBox1.Controls.Add(btn12);
      
              }
        private void btn1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("メッセージが押されました。", "メッセージ");
        }

        private void btn2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("カレンダーが押されました。", "カレンダー");
        }

        private void btn3_Click(object sender, EventArgs e)
        {
            MessageBox.Show("ビデオが押されました。", "ビデオ");
        }

        private void btn4_Click(object sender, EventArgs e)
        {

        }

        private void btn5_Click(object sender, EventArgs e)
        {

        }

        private void btn6_Click(object sender, EventArgs e)
        {

        }

        private void btn7_Click(object sender, EventArgs e)
        {

        }

        private void btn8_Click(object sender, EventArgs e)
        {

        }
        
        private void btn9_Click(object sender, EventArgs e)
        {

        }

        private void btn10_Click(object sender, EventArgs e)
        {

        }

        private void btn11_Click(object sender, EventArgs e)
        {

        }

        private void btn12_Click_1(object sender, EventArgs e)
        {

        }

        private void hombtn_Click(object sender, EventArgs e)
        {
            MessageBox.Show("ホームボタンが押されました", "Message...");
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void label11_Click(object sender, EventArgs e)
        {

        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

    }
}
