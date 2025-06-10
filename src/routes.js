
import React from 'react';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';
import MainLayout from './components/Layout/MainLayout';

const Routes = () => {
  return (
    <Router>
      <Switch>
        <Route path="/" component={MainLayout} />
      </Switch>
    </Router>
  );
};

export default Routes;
