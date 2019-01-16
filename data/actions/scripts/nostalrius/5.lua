function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and math.random(1, 100) <= 70 then 
		item:transform(2773, 1)
		item:decay()
		Game.removeItemsOnMap({x = item:getPosition().x - 1, y = item:getPosition().y, z = 14})
		Game.createItem(3242, 1, {x = item:getPosition().x - 1, y = item:getPosition().y, z = 14})
		doTargetCombatHealth(0, player, COMBAT_FIREDAMAGE, -200, -200)
	elseif item:getId() == 2772 then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemsOnMap({x = item:getPosition().x - 1, y = item:getPosition().y, z = 14})
		Game.createItem(3595, 1, {x = 33117, y = item:getPosition().y, z = 14})
		player:setStorageValue(258, 1)
		Game.sendMagicEffect({x = 33122, y = 32765, z = 14}, 15)
		Game.sendMagicEffect({x = 33117, y = 32761, z = 14}, 15)
		Game.sendMagicEffect({x = 33117, y = 32762, z = 14}, 15)
		Game.sendMagicEffect({x = 33117, y = 32763, z = 14}, 15)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.removeItemsOnMap({x = item:getPosition().x - 1, y = item:getPosition().y, z = 14})
		Game.createItem(3573, 1, {x = item:getPosition().x - 1, y = item:getPosition().y, z = 14})
	end
	return true
end