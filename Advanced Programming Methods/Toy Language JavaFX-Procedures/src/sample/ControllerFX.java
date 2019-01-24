package sample;

import Controller.Controller;
import Model.DataStructures.*;
import Model.Expressions.*;
import Model.Statements.*;
import Repository.IRepository;
import Repository.MyRepository;
import UI.Menu.ProgramState;
import com.sun.org.apache.bcel.internal.generic.ISTORE;
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

        @FXML
        private TableView<TableViewElement<String, String>> procView;

        @FXML
        private TableColumn<TableViewElement, String> ProcKey;

        @FXML
        private TableColumn<TableViewElement, String> ProcValue;

        @FXML
        private TableView<TableViewElement<Integer, String>> syncView;

        @FXML
        private TableColumn<TableViewElement, Integer> BarrKeyColumn;

        @FXML
        private TableColumn<TableViewElement, String> BarrValueColumn;

        private boolean errorThrown = false;
        private int chosenProgram = -1;
        private List<ProgramState> prgList;
        private ArrayList<Controller> controllers = new ArrayList<Controller>();
        private boolean barrier = false;
        private Stage mainStage;

        public void chooseProgramClicked() throws IOException {

                int statementsCounter = 18;

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

                IStatement ex13 = new CompoundStatement(new AssignmentStatement("c",new ConstantExpression(0)),new ConditionalStatement("d",new VariableExpression("c"), new ConstantExpression(15), new ConstantExpression(20)));
                ex.add(ex13);

                IStatement ex14 = new CompoundStatement(new AssignmentStatement("z", new ConstantExpression(1976)),new SwitchStatement(new VariableExpression("z"),new ConstantExpression(1998), new ArithmeticExpression('-',new ConstantExpression(1998), new ConstantExpression(22)),new AssignmentStatement("w",new ConstantExpression(2000)), new PrintStatement(new VariableExpression("z")),new AssignmentStatement("k", new ConstantExpression(100))));
                ex.add(ex14);

                IStatement ex15 = new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(0)), new CompoundStatement(new ForkStatement(new AssignmentStatement("v", new ConstantExpression(2))), new ForkStatement(new AssignmentStatement("v", new ConstantExpression(3)))));
                ex.add(ex15);

                IStatement ex16 = new CompoundStatement(new NewStatement("v1",new ConstantExpression(2)),
                        new CompoundStatement(new NewStatement("v2",new ConstantExpression(3)),
                                new CompoundStatement(new NewStatement("v3", new ConstantExpression(4)),
                                        new CompoundStatement(new newBarrierStatement("cnt",new ReadHeapExpression("v2")),
                                                new CompoundStatement(new ForkStatement(
                                                        new CompoundStatement(new awaitStatement("cnt"),
                                                                new CompoundStatement(new WriteHeapStatement("v1", new ArithmeticExpression('*',new ReadHeapExpression("v1"), new ConstantExpression(10))),
                                                                        new PrintStatement(new ReadHeapExpression("v1"))))),
                                                        new CompoundStatement(new ForkStatement(
                                                                new CompoundStatement(new awaitStatement("cnt"),
                                                                        new CompoundStatement(new WriteHeapStatement("v2", new ArithmeticExpression('*',new ReadHeapExpression("v2"), new ConstantExpression(10))),
                                                                                new CompoundStatement(new WriteHeapStatement("v2", new ArithmeticExpression('*',new ReadHeapExpression("v2"), new ConstantExpression(10))),
                                                                                        new PrintStatement(new ReadHeapExpression("v2"))))
                                                        )),
                                                                new CompoundStatement(new awaitStatement("cnt"), new PrintStatement(new ReadHeapExpression("v3")))
                                                ))))));
                ex.add(ex16);

                IStatement ex17 = new CompoundStatement(new AssignmentStatement("v", new ConstantExpression(10)),
                        new CompoundStatement(new ForkStatement(new CompoundStatement(new AssignmentStatement("v",new ArithmeticExpression('-',new VariableExpression("v"),new ConstantExpression(1))),
                                new CompoundStatement(new AssignmentStatement("v",new ArithmeticExpression('-',new VariableExpression("v"),new ConstantExpression(1))),
                                        new PrintStatement(new VariableExpression("v"))))),
                                new CompoundStatement(new SleepStatement(10), new PrintStatement(new ArithmeticExpression('*',new VariableExpression("v"),new ConstantExpression(10))))));
                ex.add(ex17);

                ArrayList<Expression> exp1 = new ArrayList<>();
                exp1.add(new ArithmeticExpression('*',new VariableExpression("v"), new ConstantExpression(10)));
                exp1.add(new VariableExpression("w"));

                ArrayList<Expression> exp2 = new ArrayList<>();
                exp2.add(new VariableExpression("v"));
                exp2.add(new VariableExpression("w"));

                IStatement ex18 = new CompoundStatement(new AssignmentStatement("v",new ConstantExpression(2)),
                        new CompoundStatement(new AssignmentStatement("w", new ConstantExpression(5)),
                                new CompoundStatement(new CallFctStatement("sum",exp1),
                                        new CompoundStatement(new PrintStatement(new VariableExpression("v")),
                                                new ForkStatement(new CompoundStatement(new CallFctStatement("product", exp2),
                                                        new ForkStatement(new CallFctStatement("sum",exp2))))))));
                ex.add(ex18);

                IStatement sum = new CompoundStatement(new AssignmentStatement("v",new ArithmeticExpression('+',new VariableExpression("a"), new VariableExpression("b"))),new PrintStatement(new VariableExpression("v")));
                IStatement product = new CompoundStatement(new AssignmentStatement("v",new ArithmeticExpression('*',new VariableExpression("a"), new VariableExpression("b"))),new PrintStatement(new VariableExpression("v")));

                for(int i = 0; i < statementsCounter; ++i) {
                        IStack<IStatement> exeStack = new MyStack<>();
                        Stack<IDictionary<String, Integer>> symTable = new Stack<>();
                        IDictionary<String, Integer> firstSymTable = new MyDictionary<>();
                        symTable.push(firstSymTable);
                        IList<Integer> out = new MyList<>();
                        IDictionary<Integer, Pair<String, BufferedReader>> fileTable = new MyFileTable<>();
                        IHeap<Integer, Integer> heap = new MyHeap<>();
                        IDictionary<Integer, Pair<Integer,ArrayList<Integer>>> barrierTable = new BarrierTable<>();
                        IProcTable<String, Pair<ArrayList<String>, IStatement>> procTable = new MyProcTable<>();

                        ArrayList<String> formalParameters = new ArrayList<>();
                        formalParameters.add("a");
                        formalParameters.add("b");
                        procTable.put("sum",new Pair<>(formalParameters, sum));
                        procTable.put("product",new Pair<>(formalParameters, product));
                        ProgramState prg = new ProgramState(exeStack, symTable, out, ex.get(i), fileTable, heap, barrierTable, procTable, 1);
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
                        ex12.toString(),
                        ex13.toString(),
                        ex14.toString(),
                        ex15.toString(),
                        ex16.toString(),
                        ex17.toString(),
                        ex18.toString());

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
                        if(chosenProgram > 0){
                                prgStatesCountButton.setVisible(true);
                        }
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
                ProcKey.setCellValueFactory(new PropertyValueFactory<>("key"));
                ProcValue.setCellValueFactory(new PropertyValueFactory<>("value"));
                BarrKeyColumn.setCellValueFactory(new PropertyValueFactory<>("key"));
                BarrValueColumn.setCellValueFactory(new PropertyValueFactory<>("value"));
        }

        void setMainStage(Stage primaryStage) {
                mainStage = primaryStage;
                prgStatesCountButton.setVisible(false);
        }

        @FXML
        void runOneStep(ActionEvent event) throws MyException {
                if (chosenProgram < 0) {
                        alert("No program selected!");
                }
                else{
                        prgList = Controller.removeCompletedPrg(prgList);
                        try{
                                controllers.get(chosenProgram).allStep(prgList);
                        }
                        catch(Exception e){
                                //error(e.getMessage());
                                e.printStackTrace();
                                errorThrown = true;
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

                //TableView with the barrier table
                ObservableList<TableViewElement<Integer, String>> barrTableList = FXCollections.observableArrayList();
                IDictionary<Integer, Pair<Integer, ArrayList<Integer>>> barrierTable = prgList.get(0).getBarrierTable();
                for (Integer el : barrierTable.keySet()) {
                        StringBuilder res = new StringBuilder("[");
                        boolean isFirst = true;
                        for(Integer e:barrierTable.get(el).getSecond()){
                                if(isFirst){
                                        isFirst = false;
                                }
                                else {
                                        res.append(",");
                                }
                                res.append(e.toString());
                        }
                        res.append("]");
                        barrTableList.add(new TableViewElement<>(el, barrierTable.get(el).getFirst().toString() + res));
                }
                syncView.setItems(barrTableList);

                //TableView with the proc table
                ObservableList<TableViewElement<String, String>> procTableList = FXCollections.observableArrayList();
                IProcTable<String, Pair<ArrayList<String>, IStatement>> procTable = prgList.get(0).getProcTable();
                for (String el : procTable.keySet()) {
                        StringBuilder res = new StringBuilder("(");
                        boolean isFirst = true;
                        for(String e : procTable.get(el).getFirst()){
                                if(isFirst){
                                        isFirst = false;
                                }
                                else{
                                        res.append(",");
                                }
                                res.append(e);
                        }
                        res.append(") {");
                        res.append(procTable.get(el).getSecond().toString());
                        res.append("}");
                        procTableList.add(new TableViewElement<>(el, res.toString()));
                }
                procView.setItems(procTableList);

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
                //wipeAll();
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