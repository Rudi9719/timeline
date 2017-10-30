//
//  Card.swift
//  Timeline
//
//  Created by Rudi on 10/15/17.
//  Copyright © 2017 Rudi. All rights reserved.
//

import Foundation
import SpriteKit

enum CardType: Int {
    case START,
    GAME,
    END,
    SPECIAL
}

class Card: SKSpriteNode {
    
    let cardType: CardType
    let cardFace: SKTexture
    let column: Int
    
    init(type: CardType, face: Int, column: Int) {
        self.cardType = type
        let face = SKTexture(imageNamed: "card\(face % 46 + 1)")
        cardFace = face
        self.column = column
        let size = CGSize(width: 100, height: 175)
        super.init(texture: cardFace, color: .clear, size: size)
    }
    required init?(coder aDecoder: NSCoder) {
        fatalError("NSCoding not supported.")
    }
    
}
