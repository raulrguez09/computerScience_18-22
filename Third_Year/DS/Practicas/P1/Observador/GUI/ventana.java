/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;

import org.jfree.chart.*;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.DefaultCategoryDataset;

/**
 *
 * @author raulrguez
 */
public class ventana extends javax.swing.JFrame {
    // Singleton
    private static ventana INSTANCE = new ventana();
    public boolean reiniciar = false;
    DefaultCategoryDataset dts = new DefaultCategoryDataset();
    ChartFrame f;
    

    public static ventana getInstance() {
        return INSTANCE;
    }
    
    private ventana() {
        initComponents();
        dts.setValue(0, "local", "");
        dts.setValue(0, "visitante", "");
    
        JFreeChart ch = ChartFactory.createBarChart3D("Grafica de Barras","","GOLES",dts,PlotOrientation.VERTICAL,true,true,true);
        this.f = new ChartFrame("GRAFICA OBSERVADOR", ch);
        this.f.setSize(1000, 600);
        this.f.setLocationRelativeTo(null);
        this.f.setVisible(true);
    }

    public void setPushLocal(String t){
        push_local.setText(t);
    }
    
    public void setPushVisitante(String t){
        push_visitante.setText(t);
    }
    
    public void setPullLocal(String t){
        pull_local.setText(t);
    }
    
    public void setPullVisitante(String t){
        pull_visitante.setText(t);
    }

    public void setObservableLocal(String t){
        observable_local.setText(t);
    }

    public void setObservableVisitante(String t){
        observable_visitante.setText(t);
    }
    
    public void setModLocal(String t){
        mod_local.setText(t);
    }
    
    public void setModVisitante(String t){
        mod_visitante.setText(t);
    }

    public void grafica(int local,int visitante){
        dts.setValue(local, "local", "");
        dts.setValue(visitante, "visitante", "");

        JFreeChart ch = ChartFactory.createBarChart3D("Grafica de Barras","","GOLES",dts,PlotOrientation.VERTICAL,true,true,true);
        
        ChartFrame aux = new ChartFrame("GRAFICA OBSERVADOR", ch);
        this.f = aux;
        
    }
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        observable_local = new javax.swing.JTextField();
        observable_visitante = new javax.swing.JTextField();
        observable = new javax.swing.JLabel();
        push = new javax.swing.JLabel();
        titulo = new javax.swing.JLabel();
        pull_visitante = new javax.swing.JTextField();
        push_visitante = new javax.swing.JTextField();
        push_local = new javax.swing.JTextField();
        mod = new javax.swing.JLabel();
        mod_local = new javax.swing.JTextField();
        mod_visitante = new javax.swing.JTextField();
        reiniciar_local = new javax.swing.JButton();
        pull = new javax.swing.JLabel();
        pull_local = new javax.swing.JTextField();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("INTERFAZ OBSERVER-OBSERVABLE");

        observable_local.setText("0");
        observable_local.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                observable_localActionPerformed(evt);
            }
        });

        observable_visitante.setText("0");

        observable.setText("SujetoObservable");

        push.setText("ObservadorSuscrito");

        titulo.setText("Local - Visitante");

        pull_visitante.setText("0");

        push_visitante.setText("0");

        push_local.setText("0");

        mod.setText("ObservadorMod");

        mod_local.setText("0");
        mod_local.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                mod_localActionPerformed(evt);
            }
        });

        mod_visitante.setText("0");

        reiniciar_local.setText("reiniciar_local");
        reiniciar_local.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                reiniciar_localActionPerformed(evt);
            }
        });

        pull.setText("ObservadorNoSuscrito");

        pull_local.setText("0");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addComponent(observable_local, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(observable_visitante, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(observable)
                    .addComponent(pull)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(18, 18, 18)
                        .addComponent(pull_local, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(pull_visitante, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 238, Short.MAX_VALUE)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                        .addComponent(push_local, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(push_visitante, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap())
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(push)
                            .addComponent(mod))
                        .addGap(8, 8, 8))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(reiniciar_local)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(mod_local, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(11, 11, 11)
                                .addComponent(mod_visitante, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addContainerGap())))
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(192, 192, 192)
                .addComponent(titulo)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addComponent(titulo)
                .addGap(31, 31, 31)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(observable)
                    .addComponent(push))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(observable_visitante, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(observable_local, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(push_visitante, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(push_local, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 61, Short.MAX_VALUE)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                        .addComponent(mod)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                        .addComponent(pull, javax.swing.GroupLayout.PREFERRED_SIZE, 17, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(2, 2, 2)))
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(mod_local, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(mod_visitante, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(pull_visitante, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(pull_local, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(reiniciar_local))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(108, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void observable_localActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_observable_localActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_observable_localActionPerformed

    private void mod_localActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_mod_localActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_mod_localActionPerformed

    private void reiniciar_localActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_reiniciar_localActionPerformed
        if(evt.getSource() == reiniciar_local){
           reiniciar = true;
        }
    }//GEN-LAST:event_reiniciar_localActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(ventana.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(ventana.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(ventana.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(ventana.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new ventana().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel jPanel1;
    private javax.swing.JLabel mod;
    private javax.swing.JTextField mod_local;
    private javax.swing.JTextField mod_visitante;
    private javax.swing.JLabel observable;
    private javax.swing.JTextField observable_local;
    private javax.swing.JTextField observable_visitante;
    private javax.swing.JLabel pull;
    private javax.swing.JTextField pull_local;
    private javax.swing.JTextField pull_visitante;
    private javax.swing.JLabel push;
    private javax.swing.JTextField push_local;
    private javax.swing.JTextField push_visitante;
    private javax.swing.JButton reiniciar_local;
    private javax.swing.JLabel titulo;
    // End of variables declaration//GEN-END:variables
}
