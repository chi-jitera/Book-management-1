<changes><change><info>Add comments to describe the purpose and functionality of the Routes component.</info><content>import React from 'react';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import MainLayout from './components/Layout/MainLayout';

/**
 * Routes component defines the routing for the application.
 * It sets up the main route to render the MainLayout component.
 */
const Routes = () => {
  return (
    <Router>
      <Switch>
        <Route path="/" component={MainLayout} />
      </Switch>
    </Router>
  );
};

export default Routes;</content></change>
          </changes>