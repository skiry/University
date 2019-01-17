package sample;

import Controller.Controller;
import Model.DataStructures.*;
import Model.Expressions.*;
import Model.Statements.*;
import Repository.IRepository;
import Repository.MyRepository;
import UI.Menu.ProgramState;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.*;
import java.util.List;

import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;

import static Model.DataStructures.BooleanSign.LT;

public class ControllerFX {

        @FXML
        private Button chooseProgramButton;

        @FXML
        private ListView<Integer> prgStatesView;

        @FXML
        private ListView<Integer> outView;

        @FXML
        private TableView<TableViewElement<Integer, String>> fileTableView;

        @FXML
        private TableView<TableViewElement<Integer, Integer>> heapView;

        @FXML
        private TextField prgStatesCountButton;

        @FXML
        private TableView<TableViewElement<String, Integer>> symTableView;

        @FXML
        private Button oneStepButton;

        @FXML
        private ListView<String> exeStackView;

        @FXML
        private Button programOk;

        @FXML
        private ListView<?> programsList;

        @FXML
        private TableColumn<TableViewElement, Integer> AddressColumn;

        @FXML
        private TableColumn<TableViewElement, Integer> ValueColumn;

        @FXML
        private TableColumn<TableViewElement, Integer> IdentifierColumn;

        @FXML
        private TableColumn<TableViewElement, Integer> SymValueColumn;

        @FXML
        private TableColumn<TableViewElement, String> FileNameColumn;

        @FXML
        private TableColumn<TableViewElement, String> VarNameColumn;

        boolean errorThrown = false;
        private int chosenProgram = -1;
        private List<ProgramState> prgList;
        private ArrayList<Controller> controllers = new ArrayList<Controller>();
        private boolean barrier = false;
        private Stage mainStage;

        public void chooseProgramClicked() throws IOException {

                int statementsCounter = 12;

                ArrayList<IStatement> ex = new ArrayList<>();

                IStatement ex1 = new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(2)),
                        new PrintStatement(new VariableExpression("v")));
                ex.add(ex1);

                IStatement ex2 = new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression('+', new ConstantExpression(2), new ArithmeticExpression('*', new ConstantExpression(3), new ConstantExpression(5)))), new CompoundStatement(new AssignmentStatement("b", new ArithmeticExpression('+', new VariableExpression("a"), new ConstantExpression(1))), new PrintStatement(new VariableExpression("b"))));
                ex.add(ex2);

                IStatement ex3 = new CompoundStatement(new AssignmentStatement("a", new ArithmeticExpression('-', new ConstantExpression(2), new ConstantExpression(2))), new CompoundStatement(new IfStatement(new VariableExpression("a"), new AssignmentStatement("v", new ConstantExpression(2)), new AssignmentStatement("v", new ConstantExpression(3))), new PrintStatement(new VariableExpression("v"))));
                ex.add(ex3);

                IStatement ex4 = new CompoundStatement(new openRFileStatement("var_f", "test.in"),
                        new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"),
                                new CompoundStatement(new PrintStatement(new VariableExpression("var_c")),
                                        new CompoundStatement(new IfStatement(new VariableExpression("var_c"), new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"), new PrintStatement(new VariableExpression("var_c"))), new PrintStatement(new ConstantExpression(0))),
                                                new closeRFileStatement(new VariableExpression("var_f"))))));
                ex.add(ex4);

                IStatement ex5 = new CompoundStatement(new openRFileStatement("var_f", "test.in"),
                        new CompoundStatement(new readRFileStatement(new VariableExpression("var_f+2"), "var_c"),
                                new CompoundStatement(new PrintStatement(new VariableExpression("var_c")),
                                        new CompoundStatement(new IfStatement(new VariableExpression("var_c"), new CompoundStatement(new readRFileStatement(new VariableExpression("var_f"), "var_c"), new PrintStatement(new VariableExpression("var_c"))), new PrintStatement(new ConstantExpression(0))),
                                                new closeRFileStatement(new VariableExpression("var_f"))))));
                ex.add(ex5);

                IStatement ex6 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(10)),
                        new CompoundStatement(new NewStatement("v",new ConstantExpression(20)),
                                new CompoundStatement(new NewStatement("a",new ConstantExpression(22)),
                                        new PrintStatement(new VariableExpression("v")))));
                ex.add(ex6);

                IStatement ex7 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(10)),
                        new CompoundStatement(new NewStatement("v",new ConstantExpression(20)),
                                new CompoundStatement(new NewStatement("a",new ConstantExpression(22)),
                                        new CompoundStatement(new PrintStatement(new ArithmeticExpression('+',new ConstantExpression(100),new ReadHeapExpression("v"))),
                                                new PrintStatement(new ArithmeticExpression('+',new ConstantExpression(100),new ReadHeapExpression("a")))))));
                ex.add(ex7);

                IStatement ex8 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(10)),
                        new CompoundStatement(new NewStatement("v",new ConstantExpression(20)),
                                new CompoundStatement(new NewStatement("a",new ConstantExpression(22)),
                                        new CompoundStatement(new WriteHeapStatement("a",new ConstantExpression(30)),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("a")),
                                                        new PrintStatement(new ReadHeapExpression("a")))))));
                ex.add(ex8);

                IStatement ex9 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(10)),
                        new CompoundStatement(new NewStatement("v",new ConstantExpression(20)),
                                new CompoundStatement(new NewStatement("a",new ConstantExpression(22)),
                                        new CompoundStatement(new WriteHeapStatement("a",new ConstantExpression(30)),
                                                new CompoundStatement(new PrintStatement(new VariableExpression("a")),
                                                        new CompoundStatement(new PrintStatement(new ReadHeapExpression("a")),
                                                                new AssignmentStatement("a",new ConstantExpression(0))))))));
                ex.add(ex9);

                IStatement ex10 = new PrintStatement(new ArithmeticExpression('+', new ConstantExpression(10), new BooleanExpression(LT,new ConstantExpression(2),
                        new ConstantExpression(6))));
                ex.add(ex10);

                IStatement ex11 = new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(6)),
                        new CompoundStatement(new WhileStatement(new ArithmeticExpression('-',new VariableExpression("v"), new ConstantExpression(4)),
                                new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                        new AssignmentStatement("v",new ArithmeticExpression('-',new VariableExpression("v"),new ConstantExpression(1))))),
                                new PrintStatement(new VariableExpression("v"))));
                ex.add(ex11);

                IStatement ex12 = new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(10)),

                        new CompoundStatement(new NewStatement("a", new ConstantExpression(22)),

                                new CompoundStatement(

                                        new ForkStatement(new CompoundStatement(new WriteHeapStatement("a", new ConstantExpression(30)),

                                                new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(32)),

                                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")),

                                                                new PrintStatement(new ReadHeapExpression("a")))))),

                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new ReadHeapExpression("a"))))));
                ex.add(ex12);

                for(int i = 0; i < statementsCounter; ++i) {
                        IStack<IStatement> exeStack = new MyStack<>();
                        IDictionary<String, Integer> symTable = new MyDictionary<>();
                        IList<Integer> out = new MyList<>();
                        IDictionary<Integer, Pair<String, BufferedReader>> fileTable = new MyFileTable<>();
                        IHeap<Integer, Integer> heap = new MyHeap<>();

                        ProgramState prg = new ProgramState(exeStack, symTable, out, ex.get(i), fileTable, heap, 1);
                        IRepository repo = new MyRepository(prg, "log" + Integer.toString(i + 1) + ".txt");
                        Controller ctrl = new Controller(repo);
                        controllers.add(ctrl);
                }
                ListView<String> list = new ListView<>();
                ObservableList<String> items = FXCollections.observableArrayList (
                        ex1.toString(),
                        ex2.toString(),
                        ex3.toString(),
                        ex4.toString(),
                        ex5.toString(),
                        ex6.toString(),
                        ex7.toString(),
                        ex8.toString(),
                        ex9.toString(),
                        ex10.toString(),
                        ex11.toString(),
                        ex12.toString());

                list.setItems(items);

                Button programOk = new Button("I'll go with this program!");
                VBox vbox = new VBox();
                vbox.getChildren().addAll(list, programOk);

                StackPane secondaryLayout = new StackPane();
                secondaryLayout.getChildren().add(vbox);

                Scene secondScene = new Scene(secondaryLayout, 600, 400);

                // New window (Stage)
                Stage newWindow = new Stage();
                newWindow.setTitle("Select a Program!");
                newWindow.setScene(secondScene);

                // Specifies the modality for new window.
                newWindow.initModality(Modality.WINDOW_MODAL);

                // Specifies the owner Window (parent) for new window
                newWindow.initOwner(mainStage);

                // Set position of second window, related to primary window.
                newWindow.setX(mainStage.getX() + 300);
                newWindow.setY(mainStage.getY() + 200);

                /*
                list.getSelectionModel().selectedItemProperty().addListener(
                        new ChangeListener<String>() {
                                public void changed(ObservableValue<? extends String> ov,
                                                    String old_val, String new_val) {
                                }
                        });
                */

                newWindow.show();
                programOk.setOnMouseClicked(event -> {
                        chosenProgram = list.getSelectionModel().getSelectedIndex();
                        prgList = controllers.get(chosenProgram).beforeAllStep();
                        newWindow.close();
                });
        }

        void init(){
                AddressColumn.setCellValueFactory(new PropertyValueFactory<>("key"));
                ValueColumn.setCellValueFactory(new PropertyValueFactory<>("value"));
                IdentifierColumn.setCellValueFactory(new PropertyValueFactory<>("key"));
                SymValueColumn.setCellValueFactory(new PropertyValueFactory<>("value"));
                FileNameColumn.setCellValueFactory(new PropertyValueFactory<>("value"));
                VarNameColumn.setCellValueFactory(new PropertyValueFactory<>("key"));
        }

        void setMainStage(Stage primaryStage) {
                mainStage = primaryStage;
        }

        @FXML
        void runOneStep(ActionEvent event) throws InterruptedException, MyException {
                if (chosenProgram < 0) {
                        alert("No program selected!");
                }
                else{
                        prgList = (List<ProgramState>) Controller.removeCompletedPrg(prgList);
                        try{
                                controllers.get(chosenProgram).allStep(prgList);
                        }
                        catch(Exception e){
                                error(e.getMessage());
                        }
                        int prgState = prgStatesView.getSelectionModel().getSelectedIndex();
                        if(prgList.size() != 0){
                                if(prgState == -1) {
                                        printAll(0);
                                }
                                else{
                                        if(prgState >= prgList.size()){
                                                printAll(prgList.size() - 1);
                                        }
                                        else {
                                                printAll(prgState);
                                        }
                                }
                        }
                        else{
                                alert("The program is finished!");
                                errorThrown = true;
                        }
                }
        }

        private void printAll(int count) throws MyException {
                //The number of program states
                prgStatesCountButton.setText(Integer.toString(prgList.size()));

                //ListView with the ids of each program state
                ObservableList<Integer> prgStatesIds = FXCollections.observableArrayList();
                for (ProgramState programState : prgList) {
                        prgStatesIds.add(programState.getId());
                }
                prgStatesView.setItems(prgStatesIds);

                //ListView with the Out table
                ObservableList<Integer> outList = FXCollections.observableArrayList();
                IList<Integer> outListWrapper = prgList.get(0).getOut();
                for(Iterator<Integer> itr = outListWrapper.iterator(); itr.hasNext();){
                        outList.add(itr.next());
                }
                outView.setItems(outList);

                //ListView with the execution stack of the selected program state
                ObservableList<String> exeList = FXCollections.observableArrayList();
                ArrayList<IStatement> exeStack = prgList.get(count).getExeStack().get();
                for(IStatement stmt : exeStack){
                        exeList.add(stmt.toString());
                }
                exeStackView.setItems(exeList);

                //TableView with the heap
                ObservableList<TableViewElement<Integer, Integer>> heapList = FXCollections.observableArrayList();
                HashMap<Integer, Integer> heapTable = prgList.get(0).getHeap().getHeap();
                for (Integer el : heapTable.keySet()) {
                        heapList.add(new TableViewElement<>(el, heapTable.get(el)));
                }
                heapView.setItems(heapList);

                //TableView with the symbol table
                ObservableList<TableViewElement<String, Integer>> symList = FXCollections.observableArrayList();
                IDictionary<String, Integer> symTable = prgList.get(0).getSymTable();
                for (String el : symTable.keySet()) {
                        symList.add(new TableViewElement<>(el, symTable.get(el)));
                }
                symTableView.setItems(symList);

                //TableView with the file table
                ObservableList<TableViewElement<Integer, String>> fileTableList = FXCollections.observableArrayList();
                IDictionary<Integer, Pair<String, BufferedReader>> fileTable = prgList.get(0).getFileTable();
                for (Integer el : fileTable.keySet()) {
                        fileTableList.add(new TableViewElement<>(el, fileTable.get(el).getFirst()));
                }
                fileTableView.setItems(fileTableList);

                prgStatesView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<Integer>() {
                        @Override
                        public void changed(ObservableValue<? extends Integer> observable, Integer oldValue, Integer newValue) {
                                try {
                                        int value;
                                        if((value = prgStatesView.getSelectionModel().getSelectedIndex()) != -1){
                                                updateView(value);
                                        }
                                        else{
                                                updateView(0);
                                        }
                                } catch (MyException e) {
                                        e.printStackTrace();
                                }
                        }
                });
                if(errorThrown) {
                        wipeAll();
                }
        }

        private void updateView(int count) throws MyException {
                //ListView with the execution stack of the selected program state
                ObservableList<String> exeList = FXCollections.observableArrayList();
                ArrayList<IStatement> exeStack = prgList.get(count).getExeStack().get();
                for(IStatement stmt : exeStack){
                        exeList.add(stmt.toString());
                }
                exeStackView.setItems(exeList);

                //TableView with the symbol table
                ObservableList<TableViewElement<String, Integer>> symList = FXCollections.observableArrayList();
                IDictionary<String, Integer> symTable = prgList.get(count).getSymTable();
                for (String el : symTable.keySet()) {
                        symList.add(new TableViewElement<>(el, symTable.get(el)));
                }
                symTableView.setItems(symList);
        }

        private void alert(String message){
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Warning!");
                alert.setHeaderText(null);
                alert.setContentText(message);

                alert.showAndWait();
        }

        private void error(String message){
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error !!!");
                alert.setHeaderText("Exception thrown!");
                alert.setContentText(message);

                alert.showAndWait();
                mainStage.close();
                System.exit(0);
        }

        private void wipeAll(){
                symTableView.setItems(null);
                heapView.setItems(null);
                fileTableView.setItems(null);
                outView.setItems(null);
                prgStatesView.setItems(null);
                exeStackView.setItems(null);
        }

}