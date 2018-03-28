import React, { Component } from 'react'
import Subscribe from './Subscribe'
import Episode from './Episode'

export default class App extends Component {
  constructor (props) {
    super(props)
    this.state = {
      subscribe: []
    }
  }

  componentWillMount () {
    chrome.storage.local.get({ subscribe: [] }, ({ subscribe }) => {
      this.setState({ subscribe })
    })
  }

  render () {
    return (
      <div>
        <Subscribe />
        {this.state.subscribe.map((e, index) => (
          <Episode key={index} />
        ))}
      </div>
    )
  }
}
