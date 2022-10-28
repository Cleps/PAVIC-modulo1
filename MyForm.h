#include<iostream>
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include "device_launch_parameters.h"
#include "GpuSolver.h"

//mais includes

#include<iostream>
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include "device_launch_parameters.h"
#include "GpuSolver.h"
#include <chrono>
using namespace std::chrono;

//
#include<iostream>
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <stdio.h>
#include "cuda_runtime.h"
//#include "cuda_kernel.cu"

//Load Images
#define STB_IMAGE_IMPLEMENTATION
// Write Images
#define STB_IMAGE_WRITE_IMPLEMENTATION

//#define STBIR_INCLUDE_STB_IMAGE_RESIZE_H

#include "include/stb_image.h"
//#include "include/stb_image_resize.h"
#include "include/stb_image_write.h"

using namespace std;


// FUNÇÕES 


// Convert Image to Gray at CPU
void ConvertImageToGrayCpu(unsigned char* imageRGBA, int width, int height) {


	struct Pixel
	{
		unsigned char red, green, blue;
	};
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			/*  Color to Grayscale Equation
			 Ylinear = 0.2126RLinear + 0.7152GLiners +0.0722BLiners */
			Pixel* ptrPixel = (Pixel*)&imageRGBA[y * width * 3 + 3 * x];
			unsigned char pixelValue = (unsigned char)(ptrPixel->red * 0.2126f + ptrPixel->green * 0.7152f + ptrPixel->blue * 0.0722f);

			//float pixelValue = ptrPixel->red * 0.2126f + ptrPixel->green * 0.7152f + ptrPixel-> blue * 0.0722f;
			//unsigned char pixelValue = pixelValue;
			ptrPixel->red = pixelValue;
			ptrPixel->green = pixelValue;
			ptrPixel->blue = pixelValue;
			//ptrPixel->alpha = 255;

		}
	}

}


namespace Project3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Sumário para MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Adicione o código do construtor aqui
			//
		}

	protected:
		/// <summary>
		/// Limpar os recursos que estão sendo usados.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::Button^ btn_sair;
	private: System::Windows::Forms::PictureBox^ img_input;
	private: System::Windows::Forms::PictureBox^ img_output;
	private: System::Windows::Forms::Button^ close;
	private: System::Windows::Forms::Button^ graycpu;
	private: System::Windows::Forms::Button^ graygpu;
	private: System::Windows::Forms::Label^ time_exec;
	protected:

	private:
		/// <summary>
		/// Variável de designer necessária.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necessário para suporte ao Designer - não modifique 
		/// o conteúdo deste método com o editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->btn_sair = (gcnew System::Windows::Forms::Button());
			this->img_input = (gcnew System::Windows::Forms::PictureBox());
			this->img_output = (gcnew System::Windows::Forms::PictureBox());
			this->close = (gcnew System::Windows::Forms::Button());
			this->graycpu = (gcnew System::Windows::Forms::Button());
			this->graygpu = (gcnew System::Windows::Forms::Button());
			this->time_exec = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->img_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->img_output))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(99, 363);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(110, 35);
			this->button1->TabIndex = 0;
			this->button1->Text = L"carregar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// btn_sair
			// 
			this->btn_sair->Location = System::Drawing::Point(843, 375);
			this->btn_sair->Name = L"btn_sair";
			this->btn_sair->Size = System::Drawing::Size(124, 34);
			this->btn_sair->TabIndex = 2;
			this->btn_sair->Text = L"Exit";
			this->btn_sair->UseVisualStyleBackColor = true;
			this->btn_sair->Click += gcnew System::EventHandler(this, &MyForm::btn_sair_Click);
			// 
			// img_input
			// 
			this->img_input->Location = System::Drawing::Point(50, 68);
			this->img_input->Name = L"img_input";
			this->img_input->Size = System::Drawing::Size(339, 290);
			this->img_input->TabIndex = 4;
			this->img_input->TabStop = false;
			this->img_input->Click += gcnew System::EventHandler(this, &MyForm::img_input_Click);
			// 
			// img_output
			// 
			this->img_output->Location = System::Drawing::Point(520, 68);
			this->img_output->Name = L"img_output";
			this->img_output->Size = System::Drawing::Size(352, 290);
			this->img_output->TabIndex = 5;
			this->img_output->TabStop = false;
			this->img_output->Click += gcnew System::EventHandler(this, &MyForm::img_output_Click);
			// 
			// close
			// 
			this->close->Location = System::Drawing::Point(264, 364);
			this->close->Name = L"close";
			this->close->Size = System::Drawing::Size(125, 34);
			this->close->TabIndex = 6;
			this->close->Text = L"close";
			this->close->UseVisualStyleBackColor = true;
			this->close->Click += gcnew System::EventHandler(this, &MyForm::close_Click);
			// 
			// graycpu
			// 
			this->graycpu->Location = System::Drawing::Point(67, 12);
			this->graycpu->Name = L"graycpu";
			this->graycpu->Size = System::Drawing::Size(142, 32);
			this->graycpu->TabIndex = 7;
			this->graycpu->Text = L"Gray on CPU";
			this->graycpu->UseVisualStyleBackColor = true;
			this->graycpu->Click += gcnew System::EventHandler(this, &MyForm::graycpu_Click);
			// 
			// graygpu
			// 
			this->graygpu->Location = System::Drawing::Point(246, 12);
			this->graygpu->Name = L"graygpu";
			this->graygpu->Size = System::Drawing::Size(156, 31);
			this->graygpu->TabIndex = 8;
			this->graygpu->Text = L"Gray on GPU";
			this->graygpu->UseVisualStyleBackColor = true;
			this->graygpu->Click += gcnew System::EventHandler(this, &MyForm::graygpu_Click);
			// 
			// time_exec
			// 
			this->time_exec->AutoSize = true;
			this->time_exec->Location = System::Drawing::Point(541, 27);
			this->time_exec->Name = L"time_exec";
			this->time_exec->Size = System::Drawing::Size(55, 16);
			this->time_exec->TabIndex = 9;
			this->time_exec->Text = L"Velocity";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(979, 432);
			this->Controls->Add(this->time_exec);
			this->Controls->Add(this->graygpu);
			this->Controls->Add(this->graycpu);
			this->Controls->Add(this->close);
			this->Controls->Add(this->img_output);
			this->Controls->Add(this->img_input);
			this->Controls->Add(this->btn_sair);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->img_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->img_output))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//BUTTON CARREGAR
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		// open file dialog   
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		//insert here the filter if you want
		//ofd->Filter..
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

			//img_input->Image = Image::FromFile(ofd->FileName);
			//System::String^ strFilename = ofd->FileName;

			img_input->ImageLocation = ofd->FileName;

		}
		
	}
		   /*private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		useGPU obj;
		int c[5] = {};
		int a[5] = { 0, 1, 2, 3, 4 };
		int b[5] = { 10, 11, 12, 13, 14 };

		obj.adding(c, a, b, 5);
		textBox1->Text = System::Convert::ToString(c[0]);
	}*/

		   //  EXIT CLICK
	private: System::Void btn_sair_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}

		private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	
		}
			   // PICTUREBOX INPUT
private: System::Void img_input_Click(System::Object^ sender, System::EventArgs^ e) {


}
	   // CLOSE BUTTON
private: System::Void close_Click(System::Object^ sender, System::EventArgs^ e) {
	img_input->ImageLocation = "";
	img_output->Image = nullptr;
}

	   //PICTURE BOX OUTPUT
private: System::Void img_output_Click(System::Object^ sender, System::EventArgs^ e) {
}

	   // GRAY ON CPU
private: System::Void graycpu_Click(System::Object^ sender, System::EventArgs^ e) {
	// let's downscale the image using new  width and heigh
	System::String^ file = img_input->ImageLocation;
	//bmpPicture = gcnew Bitmap(file);
	//System::String^ file = "imagens/apple.jpg";
	//bmpPicture = gcnew Bitmap(bmpPicture, down_width, down_height);
	std::string converted_xyz = msclr::interop::marshal_as< std::string >(file);
	//System::String^ teste = gcnew System::String(converted_xyz);
	int width, height, channels;
	// Loading jpeg files
	const char* c = converted_xyz.c_str();
	unsigned char* img = stbi_load(c, &width, &height, &channels, 3);

	auto start = high_resolution_clock::now();

	ConvertImageToGrayCpu(img, width, height);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	time_exec->Text = "Velocity on CPU: " + duration.count() + " microseconds";

	stbi_write_jpg("images/output.jpg", width, height, 3, img, 100);
	img_output->ImageLocation = "images/output.jpg";


}
private: System::Void graygpu_Click(System::Object^ sender, System::EventArgs^ e) {

	useGPU obj;
	System::String^ file = img_input->ImageLocation;
	std::string converted_xyz = msclr::interop::marshal_as< std::string >(file);
	int width, height, channels;
	const char* c = converted_xyz.c_str();
	unsigned char* img = stbi_load(c, &width, &height, &channels, 3);
	auto start = high_resolution_clock::now();

	obj.ImageToGrayGpu(img, width, height);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	time_exec->Text = "Velocity on GPU: " + duration.count() + " microseconds";
	stbi_write_jpg("images/output.jpg", width, height, 3, img, 100);
	img_output->ImageLocation = "images/output.jpg";
}


};


}
