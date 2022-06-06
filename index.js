import React from 'react';
import ReactDOM from 'react-dom';
//import Redux from 'redux'
//import ReactRodux from 'react-redux'
import './index.css';

class App extends React.Component{
    render() {
        return(
            <React.Fragment>
                <div className = 'navigation-menu bg-blue'>

                </div>

                <div className='menu'>

                </div>

                <div className = 'core'>

                </div>
            </React.Fragment>
        )
    }
}

ReactDOM.render(<App/>, document.getElementById("root"))