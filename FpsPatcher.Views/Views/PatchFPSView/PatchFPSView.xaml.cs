using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using FPSPatcher.ViewModels;
using Microsoft.Win32;


namespace FPSPatcher.Views {
    /// <summary>
    /// Interaction logic for PatchFPSView.xaml
    /// </summary>
    public partial class PatchFPSView : UserControl {
        public PatchFPSView() {
            InitializeComponent();
            
        }

        private void Button_Click(object sender, RoutedEventArgs e) {
            PatchFPSViewModel patchFPSViewModel = FindResource("PatchFPSViewModel") as PatchFPSViewModel;

            if(patchFPSViewModel == null)
                throw new Exception("Couldn't find the viewmodel");

            const string executableName = "TekkenGame-Win64-Shipping.exe";
            MessageBox.Show("Choose " + executableName);
            OpenFileDialog openFileDialog = new OpenFileDialog {
                                                                   Filter = $"{executableName}|{executableName}",
                                                                   InitialDirectory = patchFPSViewModel._openFileDialogStartDirectory
                                                               };

            bool? openFileDialogResult = openFileDialog.ShowDialog();

            if (openFileDialogResult != true)
                return;

            patchFPSViewModel.PatchCommand.Execute(openFileDialog.FileName);

        }
    }
}
