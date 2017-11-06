//
//  GameScene.swift
//  Timeline Shared
//
//  Created by Rudi on 10/15/17.
//  Copyright © 2017 Rudi. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    
    fileprivate var rulesNode: SKShapeNode?
    fileprivate var helpNode : SKShapeNode?
    fileprivate var cardNodes : [SKSpriteNode]?
    fileprivate var placedCards = [Card]()
    fileprivate var columnCountsUp = [1, 1, 1, 1, 1, 1, 1, 1]
    fileprivate var columnCountsDown = [1, 1, 1, 1, 1, 1, 1, 1]
    
    fileprivate var cardCounter = 0
    
    class func newGameScene() -> GameScene {
        // Load 'GameScene.sks' as an SKScene.
        guard let scene = SKScene(fileNamed: "GameScene") as? GameScene else {
            print("Failed to load GameScene.sks")
            abort()
        }
        
        // Set the scale mode to scale to fit the window
        scene.scaleMode = .aspectFill
        
        return scene
    }
    
    func setUpScene() {
        
        self.helpNode = self.childNode(withName: "//helpNode") as? SKShapeNode
        if let helpNode = self.helpNode {
            helpNode.isHidden = false
            helpNode.isUserInteractionEnabled = true
        }
        self.rulesNode = self.childNode(withName: "//rulesNode") as? SKShapeNode
        if let rulesNode = self.rulesNode {
            rulesNode.isHidden = true
            rulesNode.alpha = 1.0
            rulesNode.isUserInteractionEnabled = false
        }
        renderCard(pos: CGPoint(x: -300, y: 0))
        renderCard(pos: CGPoint(x: -200, y: 0))
        renderCard(pos: CGPoint(x: -100, y: 0))
        renderCard(pos: CGPoint(x: 0, y: 0))
        renderCard(pos: CGPoint(x: 100, y: 0))
        renderCard(pos: CGPoint(x: 200, y: 0))
        renderCard(pos: CGPoint(x: 300, y: 0))

    }
    

    override func didMove(to view: SKView) {
        self.setUpScene()
    }

    func renderCard(pos: CGPoint) {
        
        let x = pos.x
        var column = 0
        var pos2 = CGPoint(x: x, y: pos.y)
        if( x > -350 && x < -250) {
            pos2.x = -300
            column = 1
        }
        else if( x > -250 && x <= -150) {
            column = 2
            pos2.x = -200
        }
        else if( x > -150 && x <= -50) {
            column = 3
            pos2.x = -100
        }
        else if( x > -50  && x <= 50) {
            column = 4
            pos2.x = 0
        }
        else if(x>50 && x<=150) {
            column = 5
            
            pos2.x = 100
        }
        else if(x>150 && x<=250) {
            column = 6
            
            pos2.x = 200
        }
        else if(x>250 && x<=350) {
            column = 7
            
            pos2.x = 300
            
        }
        if (pos2.y >= 0) {
            pos2.y = CGFloat(Double(columnCountsUp[column] * 175)) - 175
            columnCountsUp[column] += 1
        } else {
            pos2.y = CGFloat(0.0 - Double(columnCountsDown[column] * 175))
            columnCountsDown[column] += 1
        }
        
        
        let nextCard = Card(type: .GAME, face: cardCounter, column: column)
        nextCard.position = pos2
        nextCard.zPosition = -1
        nextCard.name = "GAMECARD"
        addChild(nextCard)
        self.placedCards.append(nextCard)
        cardCounter += 1
        
    }
    func shiftColumn(at pos: CGPoint) {
        let x = pos.x
        var column = 0
        var pos2 = CGPoint(x: x, y: pos.y)
        if( x > -350 && x < -250) {
            pos2.x = -300
            column = 1
        }
        else if( x > -250 && x <= -150) {
            column = 2
            pos2.x = -200
        }
        else if( x > -150 && x <= -50) {
            column = 3
            pos2.x = -100
        }
        else if( x > -50  && x <= 50) {
            column = 4
            pos2.x = 0
        }
        else if(x>50 && x<=150) {
            column = 5
            
            pos2.x = 100
        }
        else if(x>150 && x<=250) {
            column = 6
            
            pos2.x = 200
        }
        else if(x>250 && x<=350) {
            column = 7
            
            pos2.x = 300
            
        }
        for card in placedCards {
            if card.column == column {
                
                card.position = CGPoint(x: card.position.x, y: card.position.y + 46)
            }
        }
    }
    func handleClick(at pos: CGPoint, color: SKColor) {
        let touchedNode = self.nodes(at: pos)
        if (touchedNode.last?.name ?? "" == helpNode?.name) {
            rulesNode?.isHidden = !(rulesNode?.isHidden)!
        } else if (touchedNode.last?.name ?? "" == rulesNode?.name) {
            if !(rulesNode?.isHidden)! {
                rulesNode?.isHidden = true
            }
        } else if (touchedNode.last?.name ?? "" == "GAMECARD" as String?) {
            shiftColumn(at: pos)
        } else {
            renderCard(pos: pos)
        }
        
    }
    
    override func update(_ currentTime: TimeInterval) {
        // Called before each frame is rendered
    }
}

#if os(iOS) || os(tvOS)
// Touch-based event handling
extension GameScene {

  
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        for t in touches {
            self.handleClick(at: t.location(in: self), color: SKColor.red)
        }
    }
    

    
   
}
#endif

#if os(OSX)
// Mouse-based event handling
extension GameScene {


    override func mouseUp(with event: NSEvent) {
        self.handleClick(at: event.location(in: self), color: SKColor.red)
    }

}
#endif

