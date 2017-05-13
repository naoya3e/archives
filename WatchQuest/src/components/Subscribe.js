import React, { Component } from 'react'

export default class Subscribe extends Component {
  handleSubmit (e) {
    e.preventDefault()
    const url = this.url.value

    if (!url) return

    chrome.storage.local.get({ subscribe: [] }, ({ subscribe }) => {
      chrome.storage.local.set({ subscribe: [...subscribe, url] })
    })

    document.activeElement.blur()
    this.url.value = ''
  }

  render () {
    return (
      <form onSubmit={::this.handleSubmit}>
        <input type='text' ref={(c) => { this.url = c }} placeholder='AmazonのURLを入力してください' />
      </form>
    )
  }
}
