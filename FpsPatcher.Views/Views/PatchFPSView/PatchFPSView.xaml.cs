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
using FpsPatcher.ViewModels;
using Microsoft.Win32;


namespace FpsPatcher.Views {
    /// <summary>
    /// Interaction logic for PatchFPSView.xaml
    /// </summary>
    public partial class PatchFpsView : UserControl {
        public PatchFpsView() {
            InitializeComponent();
            
        }

        private void Button_Click(object sender, RoutedEventArgs e) {
            PatchFpsViewModel patchFpsViewModel = FindResource("PatchFpsViewModel") as PatchFpsViewModel;

            if(patchFpsViewModel == null)
                throw new Exception("Couldn't find the viewmodel");

            const string executableName = "TekkenGame-Win64-Shipping.exe";
            MessageBox.Show("Choose " + executableName);
            OpenFileDialog openFileDialog = new OpenFileDialog {
                                                                   Filter = $"{executableName}|{executableName}",
                                                                   InitialDirectory = patchFpsViewModel._openFileDialogStartDirectory
                                                               };

            bool? openFileDialogResult = openFileDialog.ShowDialog();

            if (openFileDialogResult != true)
                return;

            patchFpsViewModel.PatchCommand.Execute(openFileDialog.FileName);

        }
    }
}
