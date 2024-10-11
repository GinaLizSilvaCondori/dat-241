using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;


namespace _18_9_23_paralela
{
    public partial class Form1 : Form
    {
        private Bitmap originalImage;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "Image Files|*.jpg;*.jpeg;*.png;*.bmp";
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    originalImage = new Bitmap(openFileDialog.FileName);
                    pictureBoxOriginal.Image = originalImage;
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (originalImage != null)
            {
                Bitmap edgeDetectedImage = DetectEdges(originalImage);
                pictureBoxDetect.Image = edgeDetectedImage;
            }
        }
        private Bitmap DetectEdges(Bitmap image)
        {
            // Crear una imagen para almacenar la salida
            Bitmap output = new Bitmap(image.Width, image.Height);

            // Kernel de detección de bordes (Sobel)
            int[,] gx = new int[,]
            {
                { -1, 0, 1 },
                { -2, 0, 2 },
                { -1, 0, 1 }
            };

            int[,] gy = new int[,]
            {
                { 1, 2, 1 },
                { 0, 0, 0 },
                { -1, -2, -1 }
            };

            // Procesar cada píxel
            for (int x = 1; x < image.Width - 1; x++)
            {
                for (int y = 1; y < image.Height - 1; y++)
                {
                    int pixelX = 0;
                    int pixelY = 0;

                    // Aplicar el kernel
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            Color pixelColor = image.GetPixel(x + i, y + j);
                            int grayValue = (int)(pixelColor.R * 0.299 + pixelColor.G * 0.587 + pixelColor.B * 0.114);
                            pixelX += grayValue * gx[i + 1, j + 1];
                            pixelY += grayValue * gy[i + 1, j + 1];
                        }
                    }

                    int magnitude = (int)Math.Sqrt(pixelX * pixelX + pixelY * pixelY);
                    magnitude = Math.Min(255, Math.Max(0, magnitude));

                    // Asignar el nuevo color al píxel
                    output.SetPixel(x, y, Color.FromArgb(magnitude, magnitude, magnitude));
                }
            }

            return output;
        }
    }
}
