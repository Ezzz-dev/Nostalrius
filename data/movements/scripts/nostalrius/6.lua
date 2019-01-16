function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and Tile({x = 32502, y = 31890, z = 07}):getThingCount() == 2 then
		doTargetCombatHealth(0, creature, COMBAT_POISONDAMAGE, -200, -200)
		Game.createItem(2121, 1, {x = 32497, y = 31889, z = 07})
		Game.createItem(2121, 1, {x = 32499, y = 31890, z = 07})
		Game.createItem(2121, 1, {x = 32497, y = 31890, z = 07})
		Game.createItem(2121, 1, {x = 32498, y = 31890, z = 07})
		Game.createItem(2121, 1, {x = 32496, y = 31890, z = 07})
		Game.createItem(2121, 1, {x = 32494, y = 31888, z = 07})
		Game.createItem(2121, 1, {x = 32502, y = 31890, z = 07})
	end
end
