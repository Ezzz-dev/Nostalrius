function onStepIn(creature, item, position, fromPosition)
	if Game.isItemThere({x = 32876, y = 32584, z = 10},4996) and Game.isItemThere ({x = 32823, y = 32525, z = 10},4996) and Game.isItemThere ({x = 32792, y = 32527, z = 10},4996) and Game.isItemThere ({x = 32744, y = 32586, z = 10}, 4996) then 
		doRelocate(item:getPosition(),{x = 32884, y = 32632, z = 11})
		item:getPosition():sendMagicEffect(21)
		Game.sendMagicEffect({x = 32884, y = 32632, z = 11}, 21)
	else
		doRelocate(item:getPosition(),{x = 32853, y = 32543, z = 10})
		item:getPosition():sendMagicEffect(21)
		Game.sendMagicEffect({x = 32853, y = 32543, z = 10}, 21)
		item:getPosition():sendMonsterSay("Spectral guardians ward you off.")
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32853, y = 32543, z = 10})
	item:getPosition():sendMagicEffect(21)
	Game.sendMagicEffect({x = 32853, y = 32543, z = 10}, 21)
	item:getPosition():sendMonsterSay("Spectral guardians ward you off.")
end