from sys import displayhook
from PySide2.QtWidgets import QMainWindow, QFileDialog, QMessageBox
from PySide2.QtCore import Slot
from graphic.ui_maininterface import Ui_MainWindow
from keyneededdialog import KeyNeededDialog
from keygenerateddialog import KeyGeneratedDialog
from encode import Encode
from decode import Decode

class MainInterface(QMainWindow):
    def __init__(self):
        super(MainInterface, self).__init__()
        self.encodeText = Encode()
        self.decodeText = Decode()

        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.pushButton_encode.clicked.connect(self.encode)
        self.ui.pushButton_decode.clicked.connect(self.decode)

        self.ui.actionAbrir.triggered.connect(self.openFile)
        self.ui.actionGuardar.triggered.connect(self.saveFile)

        self.ui.radioButton_encode.clicked.connect(self.changeMode)
        self.ui.radioButton_decode.clicked.connect(self.changeMode)


    @Slot()
    def encode(self):
        try:
            text = self.ui.plainTextEdit_normal.toPlainText() # Obtenemos el texto del text edit
            array = [] # Genera el arreglo que tendrá el texto cifrado y la key

            data = Encode(text)
            array = data.encodeText()

            self.ui.plainTextEdit_coded.setPlainText(array[0])
            
            QMessageBox.information( # Aviso de exito
                self,
                "Éxito",
                "Texto cifrado con éxito"
            )
            display = KeyGeneratedDialog(array[1]) # Se manda la key en otra ventana
            display.exec_()
        except:
            self.encode() # Si falla se vuelve a realizar el cifrado hasta que sea exitoso
            '''QMessageBox.critical( # Aviso de error
                self,
                "Error",
                "No se ha podido cifrar el texto"
            )''' 
            # Debido a que a veces la key generada causa error preferí volver a llamar en vez de mandar mensaje de error
        
        
    @Slot()
    def decode(self):
        display = KeyNeededDialog()
        display.exec_() # Abre el dialogo para pedir la key
        key = display.getKey() # Almacena la key obtenida del dialogo
        try: 
            codedText = self.ui.plainTextEdit_coded.toPlainText()
            data = Decode(codedText, key)

            decodedText = data.decode()

            self.ui.plainTextEdit_normal.setPlainText(decodedText)
            QMessageBox.information( # Aviso de exito
                self,
                "Éxito",
                "Texto descifrado con éxito"
            )
        except:
            QMessageBox.critical( # Aviso de error
                self,
                "Error",
                "No se ha podido descifrar el texto"
            )


    @Slot()
    def openFile(self):
        located = QFileDialog.getOpenFileName(
            self,
            'Abrir archivo',
            '.',
            'TXT (*.txt)'
        )[0]
        try:
            file = open(located, 'r')
            text = file.read()
            if(self.ui.radioButton_encode.isChecked()): # Segun la opcion elegida, el archivo abierto se pone como texto plano o cifrado
                self.ui.plainTextEdit_normal.setPlainText(text)
            else:
                self.ui.plainTextEdit_coded.setPlainText(text)
        except:
            QMessageBox.critical(
                self,
                "Error",
                "No se pudo abrir el archivo "
            )


    @Slot()
    def saveFile(self):
        located = QFileDialog.getSaveFileName(
            self,
            'Guardar archivo',
            '.',
            'TXT (*.txt)'
        )[0]
        try:
            file = open(located, 'w')
            if(self.ui.radioButton_encode.isChecked()): # Segun la opcion elegida guarda el texto plano o el cifrado
                text = self.ui.plainTextEdit_coded.toPlainText()
            else:
                text = self.ui.plainTextEdit_normal.toPlainText()
            file.write(text)
        except:
            QMessageBox.critical(
                self,
                "Error",
                "No se pudo guardar el archivo "
            )


    @Slot()
    def changeMode(self):
        self.ui.plainTextEdit_normal.clear()
        self.ui.plainTextEdit_coded.clear()
        
        if(self.ui.radioButton_encode.isChecked()):
            self.ui.plainTextEdit_normal.setReadOnly(False)
            self.ui.pushButton_encode.setDisabled(False)

            self.ui.plainTextEdit_coded.setReadOnly(True)
            self.ui.pushButton_decode.setDisabled(True)

        else:
            self.ui.plainTextEdit_normal.setReadOnly(True)
            self.ui.pushButton_encode.setDisabled(True)

            self.ui.plainTextEdit_coded.setReadOnly(False)
            self.ui.pushButton_decode.setDisabled(False)
